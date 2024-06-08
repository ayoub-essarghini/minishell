/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:47:11 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:47:55 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	with_option(char **cmds, t_envs *envs, int start)
{
	int	i;

	i = start;
	while (cmds[i])
	{
		ft_putstr_fd(cmds[i], STDOUT_FILENO);
		if (cmds[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

void	without_option(char **cmds, t_envs *envs)
{
	int	i;

	i = 1;
	while (cmds[i])
	{
		ft_putstr_fd(cmds[i], STDOUT_FILENO);
		if (cmds[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	printf("\n");
}

int	check_flag(char *cmd, int *c, int flag)
{
	if ((is_contain_n(cmd + 1) != 0))
		flag = 1;
	if (flag == 0)
	{
		if (is_contain_n(cmd + 1) == 0)
			(*c)++;
	}
	return (flag);
}

int	check_option_n(char **cmds)
{
	int	i;
	int	flag;
	int	c;

	i = 1;
	c = 1;
	flag = 0;
	if (cmds[i])
	{
		while (cmds[i])
		{
			if (cmds[i][0] == '-' && cmds[i][1] && cmds[i][1] == 'n')
				flag = check_flag(cmds[i], &c, flag);
			else
				break ;
			i++;
		}
	}
	return (c);
}

void	echo_cmd(char **cmds, t_envs *envs)
{
	int	start;

	start = 0;
	if (cmds[1])
	{
		start = check_option_n(cmds);
		if (start == 1)
			without_option(cmds, envs);
		else
			with_option(cmds, envs, start);
	}
	else
		printf("\n");
}
