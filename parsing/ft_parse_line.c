/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:14:26 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:14:29 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*creat_last_list(t_list **last)
{
	t_list	*new_last;
	t_list	*current;

	current = *last;
	new_last = NULL;
	while (current)
	{
		if (current->token == NOT_DEF)
			current = current->next;
		else
		{
			creat_last(&new_last, current->input, current->token,
				current->status);
			current = current->next;
		}
	}
	return (new_last);
}

int	ft_lexer(char *line, t_list **tab, t_list **last, t_envs **envs)
{
	t_list	*temp;

	if (check_quotes(line))
	{
		ft_split_line(tab, line);
		ft_token(*tab);
		ft_history(*tab, line);
		temp = *tab;
		*tab = check_env(*tab, envs);
		ft_free(temp);
		ft_check_concate(tab, last);
		ft_free(*tab);
		*tab = NULL;
		return (1);
	}
	else
	{
		add_history(line);
		free(line);
		ft_putendl_fd("madness shell: syntax error near quotes ", 2);
		g_exit_status = 2;
	}
	return (0);
}

int	ft_command_tab(t_list **last, t_cmd **tabcmd, t_envs **envs)
{
	t_list	*new_last;

	new_last = NULL;
	new_last = creat_last_list(last);
	if (new_last)
	{
		parse_command_tab(&new_last, tabcmd, envs);
		ft_free(new_last);
		new_last = NULL;
		return (1);
	}
	return (0);
}

int	creat_the_tab_command(t_cmd **tabcmd, t_envs **envs, t_list **last)
{
	int	check;

	check = check_syntax(*last, envs);
	if (check == 1)
	{
		if (ft_command_tab(last, tabcmd, envs))
		{
			ft_free(*last);
			*last = NULL;
			return (1);
		}
	}
	else if (!check)
		g_exit_status = 2;
	return (0);
}

int	ft_parse_line(char *line, t_cmd **tabcmd, t_envs **envs)
{
	t_list	*tab;
	t_list	*last;

	last = NULL;
	tab = NULL;
	if (ft_lexer(line, &tab, &last, envs))
	{
		if (creat_the_tab_command(tabcmd, envs, &last) == 1)
			return (1);
		ft_free(last);
		last = NULL;
	}
	return (0);
}
