/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:47:43 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 18:48:11 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	update_env_value(t_envs *env, char *key, char *new_value)
{
	t_envs	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = new_value;
			return ;
		}
		tmp = tmp->next;
	}
}

void	change_dir_cleanup(char *cwd, char *pwd, char *oldpwd)
{
	if (cwd)
		free(cwd);
	if (pwd)
		free(pwd);
	if (oldpwd)
		free(oldpwd);
}

void	set_or_append_pwd(t_envs **envs, char *key, char *value, int flag)
{
	t_envs	*tmp;
	char	*new_value;

	new_value = NULL;
	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (flag == 1)
				new_value = ft_strjoin(tmp->value, value);
			else
				check_val(value, &new_value, tmp->value);
			if (new_value)
			{
				update_env_value(*envs, key, new_value);
				return ;
			}
		}
		tmp = tmp->next;
	}
	creat_node(envs, key, value);
}

void	handle_single_arg(char **cmds, t_envs **envs)
{
	if (!cmds[1] || ft_strcmp(cmds[1], "~") == 0)
		change_to_root(envs);
	else if (cmds[1][0] == '/')
		with_relative_path(cmds, envs);
	else if (ft_strcmp(cmds[1], "-") == 0)
		change_to_old(cmds, envs);
	else if (ft_strcmp(cmds[1], "..") == 0)
		change_to_prev(cmds, envs);
	else
		with_absolute_path(cmds, envs);
}
