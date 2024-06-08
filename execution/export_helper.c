/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:50:02 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:50:07 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	print_env(t_envs **envs, int flag)
{
	t_envs	*tmp;
	t_envs	*head;

	head = dup_envs(*envs);
	tmp = head;
	if (flag == 1)
		sort_env_list(tmp);
	if (flag == 1)
		print_export(tmp);
	else
		print_env_list(tmp);
	ft_free_env(head);
}

void	check_val(char *value, char **new_value, char *tmp_value)
{
	if (!value)
		*new_value = ft_strdup(tmp_value);
	else
		*new_value = ft_strdup(value);
}

void	set_or_append_env(t_envs **envs, char *key, char *value, int flag)
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
				if (tmp->value)
					free(tmp->value);
				tmp->value = new_value;
			}
		}
		tmp = tmp->next;
	}
}

char	**convert_envs_to_arr(t_envs *envs)
{
	char	**arr;
	char	*new;
	char	*full;
	t_envs	*tmp;
	int		size;

	tmp = envs;
	size = ft_lstsize2(tmp);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
		printf("Memory allocation failed!");
	size = 0;
	while (envs)
	{
		new = ft_strjoin(envs->key, "=");
		full = ft_strjoin(new, envs->value);
		arr[size] = ft_strdup(full);
		free(new);
		free(full);
		size++;
		envs = envs->next;
	}
	arr[size] = NULL;
	return (arr);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isdigit(key[0]))
	{
		while (key[i])
		{
			if (!ft_isalnum(key[i]) && !(key[i] == '_'))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}
