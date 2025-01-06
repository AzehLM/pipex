/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:51:17 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/06 20:29:41 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include <sys/types.h>

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
	if (fd[1] > 2)
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
