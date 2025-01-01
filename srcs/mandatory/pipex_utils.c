/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:47:14 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/01 14:53:38 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*pathfinder(char *cmd, char **env)
{
	char	**env_path;
	char	*cmd_to_exec;
	char	*partial_path;
	int		i;

	i = 0;
	while (strnstr(env[i], "PATH=", 5) == 0)
		i++;
	env_path = ft_split(env[i] + 5, ':');
	i = 0;
	while (env_path[i])
	{
		partial_path = ft_strjoin(env_path[i], "/");
		cmd_to_exec = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (access(cmd_to_exec, F_OK | X_OK) == 0)
			return (cmd_to_exec);
		free(cmd_to_exec);
		i++;
	}
	free_data(env_path);
}

void	exec_cmd(char *av, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	path = pathfinder(cmd[0], env);
	if (path == 0)
	{
		free_data(cmd);
		free(path);
		//exit properly;
	}
	if (execve(path, cmd, env) == -1)
	{
		free_data(cmd);
		free(path);
		//exit properly;
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
	else if (error_code == 3)
		ft_putendl_fd("Error, invalid fd", )
	exit(error_code);
}
