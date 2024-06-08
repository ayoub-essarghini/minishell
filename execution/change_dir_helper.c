/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:46:29 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:46:33 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	handle_chdir_and_update_env(t_envs **envs, char *oldpwd, char *hamouda)
{
	char	*pwd;

	if (chdir(oldpwd) == -1)
	{
		perror("cd");
		free(oldpwd);
		g_exit_status = 1;
	}
	else
	{
		pwd = get_myenv("PWD", envs);
		if (pwd)
		{
			set_or_append_env(envs, "PWD", oldpwd, 0);
			free(pwd);
			g_exit_status = 0;
		}
		set_or_append_pwd(envs, "OLDPWD", hamouda, 0);
		ft_putendl_fd(oldpwd, 1);
	}
	free(hamouda);
	free(oldpwd);
}

void	change_to_old(char **cmds, t_envs **envs)
{
	char	*pwd;
	char	*oldpwd;
	char	*hamouda;

	pwd = NULL;
	oldpwd = NULL;
	oldpwd = get_myenv("OLDPWD", envs);
	if (oldpwd)
	{
		hamouda = getcwd(NULL, 0);
		handle_chdir_and_update_env(envs, oldpwd, hamouda);
	}
	else
	{
		ft_putendl_fd("bash: cd: OLDPWD not set", 2);
		g_exit_status = 1;
	}
}

void	change_to_prev(char **cmds, t_envs **envs)
{
	char	*oldpwd;
	char	*cwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	pwd = NULL;
	cwd = NULL;
	if (chdir("..") == -1)
	{
		perror("cd");
		g_exit_status = 1;
	}
	else
	{
		pwd = get_myenv("PWD", envs);
		cwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_or_append_env(envs, "PWD", cwd, 0);
			g_exit_status = 0;
		}
		set_or_append_pwd(envs, "OLDPWD", oldpwd, 0);
	}
	change_dir_cleanup(cwd, pwd, oldpwd);
}

void	handle_chdir_root(t_envs **envs, char *root)
{
	char	*pwd;
	char	*old;

	old = getcwd(NULL, 0);
	if (chdir(root) == -1)
	{
		perror("cd");
		g_exit_status = 1;
	}
	else
	{
		pwd = get_myenv("PWD", envs);
		if (pwd)
		{
			set_or_append_env(envs, "PWD", root, 0);
			g_exit_status = 0;
		}
		set_or_append_pwd(envs, "OLDPWD", old, 0);
	}
	change_dir_cleanup(root, pwd, old);
}

void	change_to_root(t_envs **envs)
{
	char	*root;

	root = get_myenv("HOME", envs);
	if (root)
	{
		handle_chdir_root(envs, root);
	}
	else
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_exit_status = 1;
	}
}
