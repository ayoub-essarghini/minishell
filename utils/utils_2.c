/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:35:37 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 19:37:14 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	count_heredoc(t_list *last)
{
	int	count;

	count = 0;
	while (last)
	{
		if (check_redirections(last->token))
		{
			if (!last->next)
				break ;
			else if (last->next && (check_redirections(last->next->token)
					|| last->next->token == PIPE_LINE))
				break ;
			else if (last->token == HERE_DOC)
				count++;
		}
		last = last->next;
	}
	return (count);
}

void	check_count_heredoc(int count)
{
	if (count > 16)
	{
		ft_putendl_fd("bash: maximum here-document count exceeded", 2);
		exit(2);
	}
}

char	*creat_name_heredoc(void)
{
	static int	num;
	char		*concate;
	char		*num_char;
	char		*s;

	num = 0;
	num++;
	concate = NULL;
	num_char = ft_itoa(num);
	s = "/tmp/.tmp_doc";
	concate = ft_strjoin(s, num_char);
	free(num_char);
	if (num == 34)
		num = 0;
	return (concate);
}
