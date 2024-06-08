/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:46:02 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:46:15 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	with_relative_path(char **cmds, t_envs **envs)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(cmds[1]) == -1)
	{
		perror("cd");
		g_exit_status = 1;
	}
	else
	{
		pwd = get_myenv("PWD", envs);
		if (pwd)
		{
			set_or_append_env(envs, "PWD", cmds[1], 0);
			free(pwd);
		}
		set_or_append_pwd(envs, "OLDPWD", old_pwd, 0);
		g_exit_status = 0;
	}
	if (old_pwd)
		free(old_pwd);
}

void	update_env(char *cwd, char *old_pwd, t_envs **envs)
{
	char	*pwd;

	pwd = get_myenv("PWD", envs);
	if (pwd)
	{
		set_or_append_env(envs, "PWD", cwd, 0);
		free(pwd);
	}
	set_or_append_pwd(envs, "OLDPWD", old_pwd, 0);
	g_exit_status = 0;
}

void	with_absolute_path(char **cmds, t_envs **envs)
{
	char	*old_pwd;
	char	*cwd;
	char	*root;
	char	*root2;
	char	*full_path;

	root = getcwd(NULL, 0);
	root2 = ft_strjoin(root, "/");
	full_path = ft_strjoin(root2, cmds[1]);
	free(root2);
	if (chdir(full_path) == -1)
	{
		perror("cd");
		g_exit_status = 1;
	}
	else
	{
		free(full_path);
		full_path = NULL;
		full_path = getcwd(NULL, 0);
		update_env(full_path, root, envs);
	}
	free(root);
	if (full_path)
		free(full_path);
}

void	change_directory(char **cmds, t_envs **envs)
{
	int	count;

	count = ft_strlen_arr(cmds);
	if (count < 3)
	{
		handle_single_arg(cmds, envs);
	}
	else
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		g_exit_status = 1;
	}
}
