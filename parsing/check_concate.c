/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_concate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:13:14 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:13:15 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	calcul_nodes(t_list *tab)
{
	int	count;

	count = 0;
	while (tab && tab->token != WHITE_SPACE && tab->token != HERE_DOC
		&& tab->token != REDIR_APPEND && tab->token != REDIR_IN
		&& tab->token != REDIR_OUT && tab->token != PIPE_LINE)
	{
		count++;
		tab = tab->next;
	}
	return (count);
}

int	check_token(t_list *current)
{
	if (current->token != WHITE_SPACE && current->token != HERE_DOC
		&& current->token != REDIR_APPEND && current->token != REDIR_IN
		&& current->token != REDIR_OUT && current->token != PIPE_LINE
		&& calcul_nodes(current) > 1)
		return (1);
	return (0);
}

char	*concatenate_tokens(t_list **current)
{
	char	*concate;
	char	*temp;
	t_list	*tmp;

	tmp = *current;
	temp = NULL;
	concate = ft_calloc(1, 1);
	while (*current && (*current)->token != WHITE_SPACE
		&& (*current)->token != HERE_DOC && (*current)->token != REDIR_APPEND
		&& (*current)->token != REDIR_IN && (*current)->token != REDIR_OUT
		&& (*current)->token != PIPE_LINE)
	{
		temp = ft_strjoin(concate, (*current)->input);
		free(concate);
		concate = temp;
		*current = (*current)->next;
	}
	return (concate);
}

void	ft_check_concate(t_list **tab, t_list **last)
{
	t_list	*current;
	char	*concate;

	current = *tab;
	while (current)
	{
		if (check_token(current))
		{
			concate = concatenate_tokens(&current);
			if (concate)
			{
				creat_last(last, concate, CONCATED, 0);
				free(concate);
			}
		}
		else if (current->token == WHITE_SPACE)
			current = current->next;
		else
		{
			creat_last(last, current->input, current->token, current->status);
			current = current->next;
		}
	}
}
