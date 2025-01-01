/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:33:03 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/01 14:57:17 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **av, char **env, int *fd)
{
	int	fd1;

	fd1 = open(av[1], O_RDONLY, 0777);
	if (fd1 == -1)
	{
		perror("Error");
		exit(ERR_FD);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd1, STDIN_FILENO);
	close(fd[0]);
	exec_cmd(av[2], env);
}

void	parent(char **av, char **env, int *fd)
{
	int	fd2;

	fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd2 == -1)
	{
		perror("Error");
		exit(ERR_FD);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;

	check_valid_env(env);
	if (ac != 5)
		exit_error(ERR_PARAMETERS);
	if (pipe(pid) == -1)
		strerror("need to check code errors to exit correctly");
	pid = fork();
	if (pid == -1)
		strerror("sane");
	if (!pid)
		child(av, env, fd);
	waitpid(pid, NULL, 0)l
	parent(av, env, fd);
	return (0);
}
