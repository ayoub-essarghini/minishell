/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:14:50 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:14:51 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

void	word(t_list **tab, char *line, int start, int i)
{
	char	*word;

	word = ft_word(line, start, i);
	creat_nodes(tab, word, 0);
	free(word);
}

int	simple_word(t_list **tab, char *line, int start, int i)
{
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\''
		&& line[i] != '"' && line[i] != '$' && line[i] != '|' && line[i] != '<'
		&& line[i] != '>')
		i++;
	word(tab, line, start, i);
	return (i);
}

void	ft_split_line(t_list **tab, char *line)
{
	int	i;
	int	start;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] && line[i] != '\0')
	{
		if (line[i] == '\'')
			i = single_quote(tab, line, start, i);
		else if (line[i] == '"')
			i = double_quote(tab, line, start, i);
		else if (line[i] == ' ' || line[i] == '\t')
			i = white_spaces(tab, line, start, i);
		else if (line[i] == '$')
			i = envirm(tab, line, start, i);
		else if (line[i] == '|')
			i = pipe_linee(tab, line, start, i);
		else if (line[i] == '<')
			i = redir_in(tab, line, start, i);
		else if (line[i] == '>')
			i = redir_out(tab, line, start, i);
		else
			i = simple_word(tab, line, start, i);
	}
}
