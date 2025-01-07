/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:36:51 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/07 16:16:13 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include <sys/types.h>

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
	int		*pid;
	int		infile;
	int		outfile;
	int		ac;
	char	**av;
	char	**env;
}	t_pipex;

int		check_cmd(char *cmd);
int		waiting(pid_t pid, pid_t exiter, int status);

char	*pathfinder(char *cmd, char **env);

void	check_valid_env(char **env);
void	child_process(int index, char *cmd, t_pipex *data);
void	cleanup_and_exit(t_pipex *data, int exit_code);
void	closing(t_pipex *data);
void	exec_cmd(t_pipex *data, char *av);
void	exec_cmd(t_pipex *data, char *av);
void	exit_error(t_exit_code error_code);
void	free_exec_cmd(t_pipex *data, char *path, char **cmd);
void	free_tab(char **str);
void	heredoc_handling(t_pipex *data);
void	init_pipes(t_pipex *data);
void	init_program(t_pipex *data, int ac, char **av, char **env);
void	specific_open(t_pipex *data);

#endif
