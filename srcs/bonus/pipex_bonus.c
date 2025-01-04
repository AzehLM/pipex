/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:06:25 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/04 12:32:00 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <sys/types.h>


int	specified_open(char **av, int *fd, int i)
{
	if (i == 0)
		fd[0] = open(av[1], O_RDWR | O_CREAT | O_APPEND , 0777); // in case of here_doc
	else if (i == 1)
		fd[0] = open(av[1], av[1], O_RDONLY, 0777); // for infile
	else if (i == 2)
		fd[0] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd[0] == -1)
		return (-1);
	return (fd[0]);
}

void	here_doc(char **av, char **env, int *fd)
{
	
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;

	check_valid_env(env);
	if (ac >= 5)
	{
		if (ft_strnstr("here_doc", av[1], 7) == av[1])
			here_doc(av, env, fd);
	}
	
}
