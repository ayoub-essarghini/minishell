/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:46:49 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 18:59:36 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	is_contain_n(char *str)
{
	while (*str)
	{
		if (*str != 'n')
			return (-1);
		str++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	int		i;
	char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (cmd && ft_strcmp(cmd, builtins[i]) == 0)
			return (0);
		i++;
	}
	return (-1);
}

void	handle_exit_too_many_args(int flag)
{
	g_exit_status = 1;
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	if (flag == 0)
		exit(g_exit_status);
}

void	handle_exit_numeric(char **cmds, t_cmd *tabcmd, t_envs *envs)
{
	size_t	status;

	status = ft_atoi(cmds[1]);
	ft_exit_free(tabcmd, envs);
	exit(status);
}

void	handle_exit_non_numeric(char **cmds, t_cmd *tabcmd, t_envs *envs)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmds[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	ft_exit_free(tabcmd, envs);
	exit(2);
}
