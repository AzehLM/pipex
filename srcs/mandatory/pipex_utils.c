/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:47:14 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/01 17:48:07 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdbool.h>

void	free_data(char **str)
{
	size_t		i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	check_valid_env(char **env)
{
	static int	i = 0;
	static bool	check = false;

	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) && env[i][6])
		{
			check = true;
			break ;
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
	else
		perror("Error");
	exit(error_code);
}
