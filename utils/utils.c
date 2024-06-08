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

void	print_error_msg(int flag, char *input)
{
	char	*concate;

	concate = NULL;
	if (flag == 1)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
	else if (flag == 2)
	{
		concate = ft_strjoin("minishell: syntax error near unexpected token `",
				input);
		ft_putstr_fd(concate, 2);
		ft_putstr_fd("'\n", 2);
		free(concate);
	}
}

void	ft_free(t_list *tab)
{
	t_list	*temp;

	if (tab)
	{
		while (tab != NULL)
		{
			temp = tab;
			tab = tab->next;
			if (temp->input)
				free(temp->input);
			if (temp)
				free(temp);
		}
	}
}

void	ft_free_tab_command(t_cmd *tab)
{
	t_cmd	*temp;

	if (tab)
	{
		while (tab != NULL)
		{
			temp = tab;
			tab = tab->next;
			if (temp->tab)
				ft_freedouble(temp->tab);
			if (temp->red)
				ft_free_red(temp->red);
			if (temp)
				free(temp);
		}
	}
}

void	ft_free_red(t_red *tab)
{
	t_red	*temp;

	if (tab)
	{
		while (tab != NULL)
		{
			temp = tab;
			tab = tab->next;
			if (temp->input)
				free(temp->input);
			if (temp)
				free(temp);
		}
	}
}

void	ft_free_env(t_envs *tab)
{
	t_envs	*temp;

	if (tab)
	{
		while (tab != NULL)
		{
			temp = tab;
			tab = tab->next;
			if (temp->key)
				free(temp->key);
			if (temp->value)
				free(temp->value);
			if (temp)
				free(temp);
		}
	}
}
