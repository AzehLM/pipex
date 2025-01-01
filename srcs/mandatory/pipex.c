/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:33:03 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/01 11:05:02 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **av, char **env, int *fd)
{

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
