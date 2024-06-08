/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:15:56 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:15:58 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipe(t_list *list)
{
	while (list)
	{
		if (list->token == PIPE_LINE)
			return (1);
		list = list->next;
	}
	return (0);
}

void	parse_command(t_list *current, t_cmd **tabcmd, t_type type, t_red **red)
{
	int		count;
	char	**arr;
	int		i;

	count = count_args(current);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (current)
	{
		arr[i] = ft_strdup(current->input);
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	creat_command(tabcmd, type, arr, red);
	ft_freedouble(arr);
	arr = NULL;
}

void	handle_redirections_and_parse(t_list **last, t_cmd **tabcmd,
		t_envs **envs, t_red **red)
{
	t_list	*new;

	new = ft_parse_redirections(last, red, envs);
	parse_command(new, tabcmd, pipe_line, red);
	ft_free(new);
	new = NULL;
}

void	parse_pipe(t_list *current, t_cmd **tabcmd, t_envs **envs)
{
	char	**arr;
	t_list	*new;
	t_red	*red;

	new = NULL;
	while (current)
	{
		if (current->token != PIPE_LINE)
		{
			red = NULL;
			new = NULL;
			while (current && current->token != PIPE_LINE)
			{
				creat_last(&new, current->input, current->token,
					current->status);
				current = current->next;
			}
			handle_redirections_and_parse(&new, tabcmd, envs, &red);
			ft_free_red(red);
			ft_free(new);
		}
		else
			current = current->next;
	}
}

void	parse_command_tab(t_list **list, t_cmd **tabcmd, t_envs **envs)
{
	t_list	*new;
	t_red	*red;

	red = NULL;
	if (check_pipe(*list))
	{
		parse_pipe(*list, tabcmd, envs);
	}
	else
	{
		new = ft_parse_redirections(list, &red, envs);
		parse_command(new, tabcmd, cmd, &red);
		ft_free(new);
		new = NULL;
		ft_free_red(red);
		red = NULL;
	}
}
