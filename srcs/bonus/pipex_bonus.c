/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:06:25 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/06 20:46:12 by gueberso         ###   ########.fr       */
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
		if (!partial_path)
			return (free_data(env_path), NULL);
		cmd_to_exec = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (!cmd_to_exec)
			return (free_data(env_path), NULL);
		if (access(cmd_to_exec, F_OK | X_OK) == 0)
			return (free(env_path), cmd_to_exec);
		free(cmd_to_exec);
	}
	free_data(env_path);
	return (NULL);
}

void	exec_cmd(char *av, char **env, t_pipex *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd)
	{
		free(data->pipe_fds);
		free(data->pid);
		exit_error(ERR_MALLOC);
	}
	path = pathfinder(cmd[0], env);
	if (!path)
    {
        free_data(cmd);
        free(data->pipe_fds);
        free(data->pid);
        exit(ERR_PATHFINDING);
    }
    if (execve(path, cmd, env) == -1)
    {
        free(path);
        free_data(cmd);
        free(data->pipe_fds);
        free(data->pid);
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
}

void	child_process(int index, char *cmd, t_pipex *data)
{
	int	pipe_in;
	int	pipe_out;


    if (!check_cmd(cmd))
    {
        closing(data);
        if (data->infile != -1)
            close(data->infile);
        close(data->outfile);
        free(data->pipe_fds);
        free(data->pid);
        exit(0);
    }
	if (index == 0)
	{
		pipe_in = data->infile;
		pipe_out = data->pipe_fds[1];
		if (pipe_in == -1)
		{
			closing(data);
			close(data->outfile);
			exit(0);
		}
	}
	else if (index == data->cmd_counter - 1)
	{
		pipe_in = data->pipe_fds[(index - 1) * 2];
		pipe_out = data->outfile;
	}
	else
	{
		pipe_in = data->pipe_fds[(index - 1) * 2];
		pipe_out = data->pipe_fds[index * 2 + 1];
	}
    if (dup2(pipe_in, STDIN_FILENO) == -1 || dup2(pipe_out, STDOUT_FILENO) == -1)
    {
        closing(data);
        if (data->infile != -1)
            close(data->infile);
        close(data->outfile);
        free(data->pipe_fds);
        free(data->pid);
        exit(ERR_FD);
    }
	closing(data);
	close(pipe_out);
	if (pipe_in != -1)
		close(pipe_in);
	exec_cmd(cmd, data->env, data);
}

int    main(int ac, char **av, char **env)
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
	i = 0;
	while (i < data.cmd_counter)
	{
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			exit_error(ERR_FORK);
		if (data.pid[i] == 0)
			child_process(i, data.av[i + data.cmd_start], &data);
		i++;
	}
	closing(&data);
	close(data.infile);
	close(data.outfile);
	free(data.pipe_fds);
	status = waiting(data.pid[data.cmd_counter - 1], 0, 0);
	free(data.pid);
	return (status);
}
