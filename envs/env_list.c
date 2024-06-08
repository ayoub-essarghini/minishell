/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:15 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:24:17 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envs	*ft_lstlast2(t_envs *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

int	ft_lstsize2(t_envs *lst)
{
	t_envs	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back2(t_envs **lst, t_envs *new)
{
	t_envs	*add;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			new->next = NULL;
			return ;
		}
		add = ft_lstlast2(*lst);
		add->next = new;
		new->next = NULL;
	}
}

t_envs	*ft_lstnew2(char *key, char *value)
{
	t_envs	*newnode;

	newnode = malloc(sizeof(t_envs));
	if (!newnode)
		return (NULL);
	newnode->key = ft_strdup(key);
	newnode->value = ft_strdup(value);
	newnode->next = NULL;
	return (newnode);
}

void	creat_node(t_envs **head, char *key, char *value)
{
	t_envs	*new;

	if (*head == NULL)
	{
		*head = ft_lstnew2(key, value);
	}
	else
	{
		new = malloc(sizeof(t_envs));
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->next = NULL;
		ft_lstadd_back2(head, new);
	}
}
