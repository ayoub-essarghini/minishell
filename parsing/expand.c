/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:13:21 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:13:24 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_env_doc(t_list *new, t_envs **envs)
{
	char	*str;

	str = NULL;
	if (ft_strlen(new->input) > 1 && new->input[0] == '$')
	{
		str = get_myenv(new->input + 1, envs);
		if (str)
		{
			free(new->input);
			new->input = ft_strdup(str);
		}
	}
	free(str);
}

void	split_the_env_values(t_list *tab, char *str, t_list **new)
{
	char	**arr;
	int		size;
	int		i;

	i = 0;
	arr = ft_split(str, ' ');
	size = ft_strlen_arr(arr);
	if (size > 1)
		tab->token = SPLIT_ENV;
	while (arr[i])
	{
		creat_last(new, arr[i], tab->token, tab->status);
		if (size > 1 && arr[i + 1])
			creat_last(new, " ", WHITE_SPACE, 0);
		i++;
	}
	ft_freedouble(arr);
	free(str);
}

void	get_the_value(t_list *tab, t_list **new, t_envs **envs)
{
	char	*str;

	str = get_myenv(tab->input + 1, envs);
	if (str && tab->status == 0)
	{
		split_the_env_values(tab, str, new);
	}
	else if (str && tab->status == 2)
	{
		creat_last(new, str, tab->token, tab->status);
		free(str);
	}
	else
	{
		if (tab->status == 2)
			creat_last(new, "\0", tab->token, tab->status);
		else
			creat_last(new, "\0", NOT_DEF, 0);
	}
}

t_list	*check_env(t_list *tab, t_envs **envs)
{
	t_list	*new;

	new = NULL;
	while (tab)
	{
		if (tab->token == ENV && tab->status != 1)
		{
			if (ft_strcmp("$?", tab->input) == 0)
			{
				free(tab->input);
				tab->input = ft_itoa(g_exit_status);
				creat_last(&new, tab->input, tab->token, tab->status);
			}
			else
				get_the_value(tab, &new, envs);
		}
		else
			creat_last(&new, tab->input, tab->token, tab->status);
		tab = tab->next;
	}
	return (new);
}
