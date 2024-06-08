/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:50:42 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:50:44 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	export_the_key_and_values(char *cmd, t_envs **envs, int flag)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	key = get_key(cmd);
	value = get_value(cmd);
	if (key && exist_env(key, envs) == 0)
	{
		if (is_valid_key(key))
			set_or_append_env(envs, key, value, flag);
	}
	else
		get_export(key, value, 0, envs);
	if (key)
		free(key);
	if (value)
		free(value);
}

void	sort_env_list(t_envs *head)
{
	t_envs	*current;
	t_envs	*min;
	t_envs	*next;

	current = head;
	while (current != NULL)
	{
		min = current;
		next = current->next;
		while (next != NULL)
		{
			if (ft_strcmp(next->key, min->key) < 0)
				min = next;
			next = next->next;
		}
		if (min != current)
			swap(current, min);
		current = current->next;
	}
}

t_envs	*dup_envs(t_envs *envs)
{
	t_envs	*new;

	new = NULL;
	while (envs)
	{
		creat_node(&new, envs->key, envs->value);
		envs = envs->next;
	}
	return (new);
}

int	check_key_val(char *key, char *value, int flag, t_envs **envs)
{
	if (!key && !value)
	{
		print_env(envs, flag);
		g_exit_status = 0;
		return (0);
	}
	return (1);
}

int	is_append_or_add(char *str)
{
	int	i;
	int	status;

	i = 0;
	status = 3;
	while (str[i] && str[i] != '=' && !(str[i] == '+' && (str[i + 1] == '='
				|| str[i + 1] == '+')))
		i++;
	if (str[i] == '=')
		status = 0;
	else if (str[i] == '+' && str[i + 1] == '=')
		status = 1;
	else if (str[i] == '+' && str[i + 1] == '+')
		status = -1;
	if (ft_strlen(str) == i)
		status = 2;
	return (status);
}
