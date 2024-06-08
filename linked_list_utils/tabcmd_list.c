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

t_cmd	*ft_lstlastcmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_backcmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*add;

	add = ft_lstlastcmd(*lst);
	add->next = new;
	new->prev = add;
	new->next = NULL;
}

t_red	*dublicate_red_list(t_red *red)
{
	t_red	*dub;

	dub = NULL;
	while (red)
	{
		red_list_add(&dub, red->type, red->input);
		red = red->next;
	}
	return (dub);
}

t_cmd	*ft_lstcommand(t_type type, char **arr, t_red *red)
{
	t_cmd	*newnode;

	newnode = malloc(sizeof(t_cmd));
	if (!newnode)
		return (NULL);
	newnode->tab = ft_doubledup(arr);
	newnode->red = dublicate_red_list(red);
	newnode->type = type;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}

void	creat_command(t_cmd **head, t_type type, char **arr, t_red **red)
{
	t_cmd	*new;

	if (*head == NULL)
	{
		*head = ft_lstcommand(type, arr, *red);
	}
	else
	{
		new = malloc(sizeof(t_cmd));
		new->tab = ft_doubledup(arr);
		new->red = dublicate_red_list(*red);
		new->type = type;
		new->prev = NULL;
		new->next = NULL;
		ft_lstadd_backcmd(head, new);
	}
}
