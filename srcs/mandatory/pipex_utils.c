/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:47:14 by gueberso          #+#    #+#             */
/*   Updated: 2024/12/29 15:33:00 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(t_exit_code error_code)
{
	ft_putendl_fd("Error, wrong usage. Expected:", STDERR_FILENO);
	ft_putendl_fd("./pipex infile \"cmd1\" \"cmd2\" outfile", STDERR_FILENO);
	exit(error_code);
}
