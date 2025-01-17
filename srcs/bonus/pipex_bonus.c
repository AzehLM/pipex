/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:06:25 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/17 13:51:16 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/wait.h>

int	waiting(pid_t pid, pid_t exiter, int status)
{
	static int	ret = SUCCESS;

	while (1)
	{
		exiter = wait(&status);
		if (exiter == pid)
			ret = WEXITSTATUS(status);
		if (exiter < 0)
			break ;
	}
	return (ret);
}

void	closing(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < (2 * data->pipe_counter))
		close(data->pipe_fds[i]);
	close(data->infile);
	close(data->outfile);
}

void	exit_error(t_exit_code error_code)
{
	if (error_code == 3)
		ft_putendl_fd("Error, can't find PATH in env", STDERR_FILENO);
	else if (error_code == 2)
	{
		ft_putendl_fd("Error, wrong usage. Expected:", STDERR_FILENO);
		ft_putendl_fd("./pipex fd1 \"cmd1\" \"cmd2\" fd2", STDERR_FILENO);
	}
	else if ((error_code != 2 && error_code < 128) || \
		(error_code != 3 && error_code < 128))
		perror("Error");
	exit(error_code);
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
		cleanup_and_exit(&data, ERR_MALLOC);
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
