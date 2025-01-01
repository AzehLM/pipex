/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:25:23 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/01 11:04:48 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# include <unistd.h> // fork, pipe, dup2, execve, access
# include <fcntl.h> // open, close
# include <stdlib.h> // malloc, free, exit
# include <stdio.h> // perror
# include <string.h> // strerror
# include <sys/types.h> // pid_t
# include <sys/wait.h> // waitpid

//# include <sys/stat.h> // BESOIN ?

typedef enum e_exit
{
	SUCCESS,
	ERR_ENV,
	ERR_PARAMETERS,
	ERR_MALLOC,
}	t_exit_code;

void	exit_error(t_exit_code error_code);
void	check_valid_env(char **env);

#endif
