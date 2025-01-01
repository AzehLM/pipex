/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:25:23 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/01 16:04:54 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

typedef enum e_exit
{
	SUCCESS,
	ERR_ENV,
	ERR_PARAMETERS,
	ERR_FD,
	ERR_PIPE,
	ERR_FORK,
	ERR_MALLOC,
	ERR_PATHFINDING,
	ERR_EXECVE
}	t_exit_code;

void	check_valid_env(char **env);
void	exit_error(t_exit_code error_code);
void	free_data(char **str);

#endif
