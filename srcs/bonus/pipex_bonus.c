/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:06:25 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/06 23:05:09 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
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

void	free_exec_cmd(t_pipex *data, char *path, char **cmd)
{
	if (data->pipe_fds)
		free(data->pipe_fds);
	if (data->pid)
		free(data->pid);
	if (path)
		free(path);
	if (cmd)
		free_data(cmd);
}

void	exec_cmd(char *av, char **env, t_pipex *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd)
	{
		free_exec_cmd(data, NULL, cmd);
		exit_error(ERR_MALLOC);
	}
	path = pathfinder(cmd[0], env);
	if (!path)
	{
		free_exec_cmd(data, path, cmd);
		exit(ERR_PATHFINDING);
	}
	if (execve(path, cmd, env) == -1)
	{
		free_exec_cmd(data, path, cmd);
		exit_error(ERR_EXECVE);
	}
}

void	closing(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (2 * data->pipe_counter))
	{
		close(data->pipe_fds[i]);
		i++;
	}
	close(data->infile);
	close(data->outfile);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	data;
	int		i;
	int		status;

	init_program(&data, ac, av, env);
	specific_open(&data);
	init_pipes(&data);
	data.pid = malloc(sizeof(int) * data.cmd_counter);
	if (!data.pid)
		exit_error(ERR_MALLOC);
	i = -1;
	while (++i < data.cmd_counter)
	{
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			exit_error(ERR_FORK);
		if (data.pid[i] == 0)
			child_process(i, data.av[i + data.cmd_start], &data);
	}
	closing(&data);
	status = waiting(data.pid[data.cmd_counter - 1], 0, 0);
	free(data.pipe_fds);
	free(data.pid);
	return (status);
}
