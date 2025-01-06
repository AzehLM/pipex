/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:06:25 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/06 15:43:44 by gueberso         ###   ########.fr       */
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
		if (!cmd_to_exec)
			return (free_data(env_path), NULL);
		free(partial_path);
		if (access(cmd_to_exec, F_OK | X_OK) == 0)
			return (free(env_path), cmd_to_exec);
		free(cmd_to_exec);
	}
	free_data(env_path);
	return (NULL);
}

void	exec_cmd(char *av, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd)
		exit_error(ERR_MALLOC);
	path = pathfinder(cmd[0], env);
	if (!path)
	{
		free_data(cmd);
		exit_error(ERR_PATHFINDING);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		free_data(cmd);
		exit_error(ERR_EXECVE);
	}
}

void	close_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (2 * data->pipe_counter))
	{
		close(data->pipe_fds[i]);
		i++;
	}
}

void	init_pipes(t_pipex *data)
{
	int	i;

	data->pipe_fds = (int *)malloc(sizeof(int) * 2 * data->pipe_counter);
	if (!data->pipe_fds)
		exit_error(ERR_MALLOC);
	i = 0;
	while (i < data->pipe_counter)
	{
		if (pipe(data->pipe_fds + (i * 2)) == -1)
		{
			while (i--)
			{
				close(data->pipe_fds[i * 2]);
				close(data->pipe_fds[i * 2 + 1]);
			}
			free(data->pipe_fds);
			exit_error(ERR_PIPE);
		}
		i++;
	}
}

void	heredoc_handling(t_pipex *data)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error(ERR_PIPE);
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			close(fd[0]);
			close(fd[1]);
			exit_error(ERR_MALLOC);
		}
		if (ft_strncmp(line, data->av[2], ft_strlen(data->av[2])) == 0 && \
			line[ft_strlen(data->av[2])] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	data->infile = fd[0];
	close(fd[1]);
}

void	specific_open(t_pipex *data)
{
	if (ft_strncmp(data->av[1], "here_doc", 8) == 0 && data->ac >= 6)
	{
		data->cmd_counter = data->ac - 4;
		data->pipe_counter = data->cmd_counter - 1;
		data->outfile = open(data->av[data->ac - 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		heredoc_handling(data);
		data->cmd_start = 3;
	}
	else
	{
		data->cmd_counter = data->ac - 3;
		data->pipe_counter = data->cmd_counter - 1;
		data->infile = open(data->av[1], O_RDONLY, 0777);
		if (data->infile == -1)
			perror("Error");
		data->outfile = open(data->av[data->ac - 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		data->cmd_start = 2;
	}
}

void	init_program(t_pipex *data, int ac, char **av, char **env)
{
	check_valid_env(env);
	if (ac < 5)
		exit_error(ERR_PARAMETERS);
	data->ac = ac;
	data->av = av;
	data->env = env;
}

void	child_process(int index, char *cmd, t_pipex *data)
{
	int	pipe_in;
	int	pipe_out;

	if (index == 0)
	{
		pipe_in = data->infile;
		pipe_out = data->pipe_fds[1];
		if (pipe_in == -1)
		{
			close_pipes(data);
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
		exit_error(EXIT_FAILURE);
	close_pipes(data);
	if (pipe_in != -1)
		close(pipe_in);
	close(pipe_out);
	if (!check_cmd(cmd))
		exit_error(ERR_EMPTY_CMD);
	exec_cmd(cmd, data->env);
}

int    main(int ac, char **av, char **env)
{
	t_pipex	data;
	int		i;
	int		status;

	init_program(&data, ac, av, env);
	specific_open(&data);
	// if (data.infile == -1 || data.outfile == -1)
	// 	exit_error(ERR_FD);
	init_pipes(&data);
	data.pid = malloc(sizeof(pid_t) * data.cmd_counter);
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
	close_pipes(&data);
	close(data.infile);
	close(data.outfile);
	status = waiting(data.pid[data.cmd_counter - 1], 0, 0);
	free(data.pipe_fds);
	free(data.pid);
	return (status);
}
