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

t_red	*ft_lstred(t_token type, char *input)
{
	t_red	*newnode;

	newnode = malloc(sizeof(t_red));
	if (!newnode)
		return (NULL);
	newnode->input = ft_strdup(input);
	newnode->type = type;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}

t_red	*ft_lstlastred(t_red *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_red(t_red **lst, t_red *new)
{
	t_red	*add;

	add = ft_lstlastred(*lst);
	add->next = new;
	new->prev = add;
	new->next = NULL;
}

void	ft_lstadd_redfront(t_red **lst, t_red *new)
{
	if (!new)
		return ;
	new->next = *lst;
	if (*lst)
		(*lst)->prev = new;
	*lst = new;
}

void	red_list_add(t_red **head, t_token type, char *input)
{
	t_red	*new;

	if (*head == NULL)
	{
		*head = ft_lstred(type, input);
	}
	else
	{
		new = malloc(sizeof(t_cmd));
		new->input = ft_strdup(input);
		new->type = type;
		new->prev = NULL;
		new->next = NULL;
		ft_lstadd_red(head, new);
	}
}
