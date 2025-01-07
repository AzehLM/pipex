/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:40:35 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/07 13:32:03 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include <sys/types.h>

static void	first_child(t_pipex *data, int *pipe_in, int *pipe_out)
{
	*pipe_in = data->infile;
	*pipe_out = data->pipe_fds[1];
	if (*pipe_in == -1)
		cleanup_and_exit(data, 0);
}

static void	last_child(t_pipex *data, int index, int *pipe_in, int *pipe_out)
{
	*pipe_in = data->pipe_fds[(index - 1) * 2];
	*pipe_out = data->outfile;
}

static void	middle_child(t_pipex *data, int index, int *pipe_in, int *pipe_out)
{
	*pipe_in = data->pipe_fds[(index - 1) * 2];
	*pipe_out = data->pipe_fds[index * 2 + 1];
}

static void	setup_pipes(t_pipex *data, int pipe_in, int pipe_out)
{
	if (dup2(pipe_in, STDIN_FILENO) == -1 || \
		dup2(pipe_out, STDOUT_FILENO) == -1)
		cleanup_and_exit(data, ERR_FD);
	closing(data);
	close(pipe_out);
	if (pipe_in != -1)
		close(pipe_in);
	close(data->outfile);
	close(data->infile);
}

void	child_process(int index, char *cmd, t_pipex *data)
{
	int	pipe_in;
	int	pipe_out;

	if (!check_cmd(cmd))
		cleanup_and_exit(data, 0);
	if (index == 0)
		first_child(data, &pipe_in, &pipe_out);
	else if (index == data->cmd_counter - 1)
		last_child(data, index, &pipe_in, &pipe_out);
	else
		middle_child(data, index, &pipe_in, &pipe_out);
	setup_pipes(data, pipe_in, pipe_out);
	exec_cmd(data, cmd);
}
