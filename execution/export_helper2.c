/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:50:20 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:50:24 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	free_env_node(t_envs *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	swap(t_envs *a, t_envs *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	remove_env_key(char *key_to_remove, t_envs **envs)
{
	t_envs	*to_free;
	t_envs	*tmp;
	t_envs	*prev;

	prev = NULL;
	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key_to_remove) == 0)
		{
			if (prev == NULL)
				*envs = tmp->next;
			else
				prev->next = tmp->next;
			to_free = tmp;
			tmp = tmp->next;
			free_env_node(to_free);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	remove_env(char **cmds, t_envs **envs)
{
	int	i;

	i = 1;
	while (cmds[i])
	{
		remove_env_key(cmds[i], envs);
		i++;
	}
}

int	exist_env(char *key, t_envs **envs)
{
	t_envs	*tmp;

	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}
