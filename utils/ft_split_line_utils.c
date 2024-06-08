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

int	envirm(t_list **tab, char *line, int start, int i)
{
	start = i;
	i++;
	if (line[i] == '?' || isdigit(line[i]))
		i++;
	else
	{
		while (line[i] && (ft_isalnum(line[i]) || line[i] == '_')
			&& line[i] != '\t')
			i++;
	}
	word(tab, line, start, i);
	return (i);
}

int	pipe_linee(t_list **tab, char *line, int start, int i)
{
	start = i;
	i++;
	word(tab, line, start, i);
	return (i);
}

int	redir_in(t_list **tab, char *line, int start, int i)
{
	int	count;

	count = 0;
	start = i;
	while (line[i] == '<' && count < 2)
	{
		i++;
		count++;
	}
	word(tab, line, start, i);
	return (i);
}

int	redir_out(t_list **tab, char *line, int start, int i)
{
	int	count;

	count = 0;
	start = i;
	while (line[i] == '>' && count < 2)
	{
		i++;
		count++;
	}
	word(tab, line, start, i);
	return (i);
}

int	white_spaces(t_list **tab, char *line, int start, int i)
{
	start = i;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	word(tab, line, start, i);
	return (i);
}
