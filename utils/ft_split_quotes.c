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

int	spaces_quotes(t_list **tab, char *str, int start, int i)
{
	char	*word;

	start = i;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	word = ft_word(str, start, i);
	creat_nodes(tab, word, 2);
	free(word);
	return (i);
}

int	envrm_quotes(t_list **tab, char *str, int start, int i)
{
	char	*word;
	int		count;

	start = i;
	i++;
	if (str[i] == '?' || isdigit(str[i]))
		i++;
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')
			&& str[i] != '\t')
			i++;
	}
	word = ft_word(str, start, i);
	creat_nodes(tab, word, 2);
	free(word);
	return (i);
}

void	ft_split_words(t_list **tab, char *str, int status)
{
	int		i;
	int		start;
	char	*word;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i = spaces_quotes(tab, str, start, i);
		if (str[i] == '$')
			i = envrm_quotes(tab, str, start, i);
		else
		{
			start = i;
			while (str[i] != ' ' && str[i] != '\t' && str[i] && str[i] != '$')
				i++;
			word = ft_word(str, start, i);
			creat_nodes(tab, word, status);
			free(word);
		}
	}
}

int	double_quote(t_list **tab, char *line, int start, int i)
{
	char	*word;

	i++;
	start = i;
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] == '"')
	{
		word = ft_word(line, start, i);
		if (ft_strcmp(word, "\0") == 0)
			creat_nodes(tab, "\0", 2);
		else
			ft_split_words(tab, word, 2);
		free(word);
	}
	i++;
	return (i);
}

int	single_quote(t_list **tab, char *line, int start, int i)
{
	char	*word;

	i++;
	start = i;
	while (line[i] && line[i] != '\'')
		i++;
	if (line[i] == '\'')
	{
		word = ft_word(line, start, i);
		creat_nodes(tab, word, 1);
		free(word);
	}
	i++;
	return (i);
}
