/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:36:51 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/06 13:04:14 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

typedef enum e_exit
{
	SUCCESS,
	ERR_FD,
	ERR_PARAMETERS,
	ERR_ENV,
	ERR_PIPE,
	ERR_FORK,
	ERR_MALLOC,
	ERR_EMPTY_CMD,
	ERR_EXECVE,
	ERR_PATHFINDING = 127,
}	t_exit_code;

typedef struct s_pipex
{
	int		cmd_counter;
	int		cmd_start;
	int		pipe_counter;
	int		*pipe_fds;
	int		*pid; // ?? allocation ou fermeture a chaque utilisation ?
	int		infile;
	int		outfile;
	int		ac;
	char	**av;
	char	**env;
}	t_pipex;

int		check_cmd(char *cmd);
int		waiting(pid_t pid, pid_t exiter, int status);

void	check_valid_env(char **env);
void	exit_error(t_exit_code error_code);
void	free_data(char **str);

#endif
