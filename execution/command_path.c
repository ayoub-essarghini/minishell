/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:45:02 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:45:19 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*get_path_from_env(t_envs **envs)
{
	char	*path;

	path = get_myenv("PATH", envs);
	return (path);
}

char	**split_paths(char *get_path)
{
	char	**paths;

	paths = ft_split(get_path, ':');
	return (paths);
}

char	*construct_full_cmd(char *path, char *cmd)
{
	char	*new_cmd;
	char	*full_cmd;

	new_cmd = ft_strjoin(path, "/");
	if (!new_cmd)
		return (NULL);
	full_cmd = ft_strjoin(new_cmd, cmd);
	free(new_cmd);
	return (full_cmd);
}

char	*find_executable(char **paths, char *cmd)
{
	int		i;
	char	*full_cmd;

	i = 0;
	while (paths[i])
	{
		full_cmd = construct_full_cmd(paths[i], cmd);
		if (!full_cmd)
		{
			ft_freedouble(paths);
			return (NULL);
		}
		if (access(full_cmd, F_OK) == 0)
		{
			ft_freedouble(paths);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	ft_freedouble(paths);
	return (NULL);
}

char	*get_cmd_bin(char **args, t_envs **envs)
{
	char	*get_path;
	char	**paths;
	char	*cmd;

	cmd = NULL;
	if (args[0] == NULL || args[0][0] == '\0')
		return (NULL);
	get_path = get_path_from_env(envs);
	if (!get_path)
		return (NULL);
	paths = split_paths(get_path);
	free(get_path);
	if (!paths)
		return (NULL);
	cmd = find_executable(paths, args[0]);
	return (cmd);
}
