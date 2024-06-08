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

void	ft_history(t_list *tab, char *line)
{
	int	flag;
	int	count;

	count = 0;
	flag = 0;
	while (tab)
	{
		if (tab->token == HERE_DOC)
		{
			count++;
			flag = 1;
		}
		tab = tab->next;
	}
	if (flag == 0)
		add_history(line);
	free(line);
}

int	check_redirections(t_token type)
{
	if (type == HERE_DOC || type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND)
		return (1);
	return (0);
}

int	check_line(char *str)
{
	if (ft_strlen(str) > 0)
	{
		if (!all_space(str) || (ft_strcmp(str, "\0")) == 0)
		{
			free(str);
			return (0);
		}
	}
	else
	{
		free(str);
		return (0);
	}
	return (1);
}

int	all_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	all_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z')))
			return (0);
		i++;
	}
	return (1);
}
