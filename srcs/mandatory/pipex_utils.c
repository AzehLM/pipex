/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:47:14 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/01 11:04:27 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_valid_env(char **env)
{
	static int	i = 0;
	static bool	check = false;

	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) && env[i][6])
		{
			check = true;
			break;
		}
		i++;
	}
	if (check == false)
		exit_error(ERR_ENV);
}

void	exit_error(t_exit_code error_code)
{
	if (error_code == 1)
		ft_putendl_fd("Error, invalid PATH env", STDERR_FILENO);
	else if (error_code == 2)
	{
		ft_putendl_fd("Error, wrong usage. Expected:", STDERR_FILENO);
		ft_putendl_fd("./pipex fd1 \"cmd1\" \"cmd2\" fd2", STDERR_FILENO);
	}
	exit(error_code);
}
