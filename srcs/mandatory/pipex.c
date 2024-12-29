/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:33:03 by gueberso          #+#    #+#             */
/*   Updated: 2024/12/29 15:32:27 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	//int		fd[2];
	//pid_t	pid;
	
	(void) ac;
	(void) av;
	(void) env;
	

	if (ac != 5)
		exit_error(ERR_LOW_PARAM);
	else
	{
		ft_printf("test\n");
	}
	return (110);
}
