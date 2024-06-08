/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:48:11 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 18:50:12 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	valid_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **cmds, t_cmd *tabcmd, t_envs *envs, int flag)
{
	int	count;

	count = ft_strlen_arr(cmds);
	if (flag == 1)
		ft_putendl_fd("exit", 2);
	if (count > 1)
	{
		if (valid_numeric(cmds[1]))
		{
			if (count > 2)
				handle_exit_too_many_args(flag);
			else
				handle_exit_numeric(cmds, tabcmd, envs);
		}
		else
			handle_exit_non_numeric(cmds, tabcmd, envs);
	}
	else
	{
		ft_exit_free(tabcmd, envs);
		exit(0);
	}
}

void	second_part(char **cmds, t_red *red, t_envs **envs)
{
	char	*pwd;

	if (cmds && ft_strcmp(cmds[0], "echo") == 0)
	{
		echo_cmd(cmds, *envs);
		g_exit_status = 0;
	}
	else if (cmds && ft_strcmp(cmds[0], "cd") == 0)
		change_directory(cmds, envs);
	else if (cmds && ft_strcmp(cmds[0], "pwd") == 0)
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
			printf("%s\n", pwd);
		free(pwd);
		g_exit_status = 0;
	}
}

void	exec_builtin(t_cmd *tabcmd, char **cmds, t_red *red, t_envs **envs)
{
	if (cmds && ft_strcmp(cmds[0], "env") == 0)
		get_export(NULL, NULL, 0, envs);
	else if (cmds && ft_strcmp(cmds[0], "exit") == 0)
		ft_exit(cmds, tabcmd, *envs, 1);
	else if (cmds && ft_strcmp(cmds[0], "export") == 0)
	{
		if (!cmds[1])
			get_export(NULL, NULL, 1, envs);
		else
			set_export(cmds, envs);
	}
	else if (cmds && ft_strcmp(cmds[0], "unset") == 0)
	{
		if (cmds[1])
		{
			remove_env(cmds, envs);
			g_exit_status = 0;
		}
		else
			g_exit_status = 0;
	}
	second_part(cmds, red, envs);
}
