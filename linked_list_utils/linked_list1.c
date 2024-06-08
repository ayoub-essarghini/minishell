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

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
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

int	count_args(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

char	**convert_list_to_arr(t_list *lst)
{
	int		count;
	char	**arr;
	int		i;

	count = ft_lstsize(lst);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (lst)
	{
		arr[i] = ft_strdup(lst->input);
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	creat_last(t_list **head, char *input, t_token token, t_state status)
{
	t_list	*new;

	if (*head == NULL)
	{
		*head = ft_lstnewlast(input, token, status);
	}
	else
	{
		new = malloc(sizeof(t_list));
		new->input = ft_strdup(input);
		new->status = status;
		new->token = token;
		new->prev = NULL;
		new->next = NULL;
		ft_lstadd_back(head, new);
	}
}

t_list	*ft_lstnewlast(char *input, t_token token, t_state status)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->input = ft_strdup(input);
	newnode->status = status;
	newnode->token = token;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}
