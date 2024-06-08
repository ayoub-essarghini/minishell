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

int	check_prev_token(t_list *tab)
{
	if (tab && tab->prev)
	{
		tab->token = WORD;
		while (tab && tab->token != WHITE_SPACE)
			tab = tab->prev;
		if (tab && tab->token == WHITE_SPACE && tab->prev
			&& tab->prev->token == HERE_DOC)
			return (1);
	}
	return (0);
}

void	token_env(t_list *tab)
{
	if (check_prev_token(tab))
		tab->token = WORD;
	else
		tab->token = ENV;
}

void	ft_token(t_list *tab)
{
	while (tab)
	{
		if (ft_strlen(tab->input) > 1 && tab->input[0] == '$')
			token_env(tab);
		else if (ft_strcmp(tab->input, "|") == 0 && tab->status == 0)
			tab->token = PIPE_LINE;
		else if (ft_strcmp(tab->input, "<") == 0 && tab->status == 0)
			tab->token = REDIR_IN;
		else if (ft_strcmp(tab->input, ">") == 0 && tab->status == 0)
			tab->token = REDIR_OUT;
		else if (ft_strcmp(tab->input, ">>") == 0 && tab->status == 0)
			tab->token = REDIR_APPEND;
		else if (ft_strcmp(tab->input, "<<") == 0 && tab->status == 0)
			tab->token = HERE_DOC;
		else if (!all_space(tab->input) && tab->status == 0)
			tab->token = WHITE_SPACE;
		else if (!all_space(tab->input) && tab->status != 0)
			tab->token = QUOTES_SPACES;
		else
			tab->token = WORD;
		tab = tab->next;
	}
}
