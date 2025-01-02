/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:25:23 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/02 20:35:26 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

// # include <string.h>
// # include <errno.h>

typedef enum e_exit
{
	SUCCESS,
	ERR_ENV,
	ERR_PARAMETERS,
	ERR_FD,
	ERR_PIPE,
	ERR_FORK,
	ERR_MALLOC,
	ERR_EMPTY_CMD,
	ERR_EXECVE,
	ERR_PATHFINDING = 127,
}	t_exit_code;

int		check_cmd(char *cmd);
int		waiting(pid_t pid, int status, pid_t exiter);

void	check_valid_env(char **env);
void	exit_error(t_exit_code error_code);
void	free_data(char **str);

#endif
