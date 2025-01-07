/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:47:14 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/07 15:16:38 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	cleanup_and_exit(t_pipex *data, int exit_code)
{
	closing(data);
	if (data->infile != -1)
		close(data->infile);
	close(data->outfile);
	free(data->pipe_fds);
	free(data->pid);
	exit(exit_code);
}



void	check_valid_env(char **env)
{
	static int	i = 0;
	static bool	check = false;

	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) && env[i][5])
		{
			check = true;
			break ;
		}
		i++;
	}
	if (check == false)
		exit_error(ERR_ENV);
}

int	check_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (!ft_isspace(cmd[i]))
			return (true);
		i++;
	}
	return (false);
}
