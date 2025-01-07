/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:41:24 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/07 16:16:23 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*pathfinder(char *cmd, char **env)
{
	char	**env_path;
	char	*cmd_to_exec;
	char	*partial_path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	env_path = ft_split(env[i] + 5, ':');
	if (!env_path)
		return (0);
	i = -1;
	while (env_path[++i])
	{
		partial_path = ft_strjoin(env_path[i], "/");
		cmd_to_exec = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (access(cmd_to_exec, F_OK | X_OK) == 0)
			return (free(env_path), cmd_to_exec);
		free(cmd_to_exec);
	}
	free_tab(env_path);
	return (0);
}

void	free_exec_cmd(t_pipex *data, char *path, char **cmd)
{
	if (data->pipe_fds)
		free(data->pipe_fds);
	if (data->pid)
		free(data->pid);
	if (path)
		free(path);
	if (cmd)
		free_tab(cmd);
}

void	exec_cmd(t_pipex *data, char *av)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd)
	{
		free_exec_cmd(data, NULL, cmd);
		exit_error(ERR_MALLOC);
	}
	path = pathfinder(cmd[0], data->env);
	if (!path)
	{
		free_exec_cmd(data, path, cmd);
		exit(ERR_PATHFINDING);
	}
	if (execve(path, cmd, data->env) == -1)
	{
		free_exec_cmd(data, path, cmd);
		exit_error(ERR_EXECVE);
	}
}
