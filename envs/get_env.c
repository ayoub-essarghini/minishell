/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:15 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 19:21:39 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_myenv(char *key, t_envs **envs)
{
	t_envs	*tmp;
	char	*value;

	value = NULL;
	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			value = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
	return (value);
}

char	*get_mycwd(t_envs *env_list)
{
	t_envs	*tmp;
	char	*pwd;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			pwd = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	ft_free_env(tmp);
	return (pwd);
}

void	set_envs_list(int ac, char *av[], char *envs[], t_envs **env_list)
{
	(void)ac;
	(void)av;
	if (envs[0] == NULL)
		set_defautl_env(env_list);
	else
		set_envs(envs, env_list);
}
