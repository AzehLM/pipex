/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:33:03 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/02 20:41:54 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <sys/types.h>


char	*pathfinder(char *cmd, char **env)
{
	char	**env_path;
	char	*cmd_to_exec;
	char	*partial_path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	env_path = ft_split(env[i] + 5, ':');
	if (!env_path)
		return (0);
	i = -1;
	while (env_path[++i])
	{
		partial_path = ft_strjoin(env_path[i], "/");
		cmd_to_exec = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (access(cmd_to_exec, F_OK | X_OK) == 0)
			return (free(env_path), cmd_to_exec);
		free(cmd_to_exec);
	}
	free_data(env_path);
	return (0);
}

void	exec_cmd(char *av, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd)
		exit_error(ERR_MALLOC);
	path = pathfinder(cmd[0], env);
	if (path == 0)
	{
		free_data(cmd);
		free(path);
		exit_error(ERR_PATHFINDING);
	}
	if (execve(path, cmd, env) == -1)
	{
		free_data(cmd);
		free(path);
		exit_error(ERR_EXECVE);
	}
	free(path);
	free_data(cmd);
}

void	child(char **av, char **env, int *fd)
{
	int	infile;

	close(fd[0]);
	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
		exit_error(ERR_FD);
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[1]);
	close(infile);
	if (!av[2] || !check_cmd(av[2]))
		exit_error(ERR_EMPTY_CMD);
	exec_cmd(av[2], env);
}

void	parent(char **av, char **env, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		exit_error(ERR_FD);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	if (!av[3] || !check_cmd(av[3]))
		exit_error(ERR_EMPTY_CMD);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;

	check_valid_env(env);
	if (ac != 5)
		exit_error(ERR_PARAMETERS);
	if (pipe(fd) == -1)
		exit_error(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		exit_error(ERR_FORK);
	if (pid == 0)
		child(av, env, fd);
	close(fd[1]);
	pid = fork();
	if (pid == -1)
		exit_error(ERR_FORK);
	if (pid == 0)
		parent(av, env, fd);
	close(fd[0]);
	return (waiting(pid, 0, 0));
}
