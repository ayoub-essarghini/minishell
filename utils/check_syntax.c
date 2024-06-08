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

int	check_quotes(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
			if (line[i] != c)
			{
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	ambiguous_redirect(t_list *last)
{
	if (check_redirections(last->token))
	{
		if (last->token != HERE_DOC && (last->next->token == NOT_DEF
				|| last->next->token == SPLIT_ENV))
		{
			ft_putstr_fd("-minishell: $: ambiguous redirect\n", 2);
			return (1);
		}
	}
	return (0);
}

int	pipe_line_syntax(t_list *last)
{
	if (last->token == PIPE_LINE)
	{
		if (!last->prev || !last->next || (last->next
				&& last->next->token == PIPE_LINE))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'",
				2);
			return (1);
		}
	}
	return (0);
}

int	redirections_syntax(t_list *last, t_envs **envs, int count)
{
	check_count_heredoc(count);
	if (check_redirections(last->token))
	{
		if (!last->next)
		{
			print_error_msg(1, last->input);
			return (0);
		}
		else if (last->next && (check_redirections(last->next->token)
				|| last->next->token == PIPE_LINE))
		{
			print_error_msg(2, last->next->input);
			return (0);
		}
		else if (last->token == HERE_DOC)
		{
			if (parse_here_doc(last, envs) == 130)
				return (130);
		}
	}
	return (1);
}

int	check_syntax(t_list *tab, t_envs **envs)
{
	t_list	*current;
	int		check;
	int		count;

	check = 1;
	current = tab;
	count = count_heredoc(current);
	while (current)
	{
		check = redirections_syntax(current, envs, count);
		if (check == 0 || check == 130)
			return (check);
		if (pipe_line_syntax(current))
			return (0);
		current = current->next;
	}
	while (tab)
	{
		if (ambiguous_redirect(tab))
			return (0);
		tab = tab->next;
	}
	return (1);
}
