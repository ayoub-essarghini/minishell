/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:49:43 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:49:47 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	print_export(t_envs *current)
{
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		if (current->value)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

void	print_env_list(t_envs *current)
{
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		current = current->next;
	}
}

void	get_export(char *key, char *value, int flag, t_envs **envs)
{
	char	*error_cmd;
	char	*full_err;

	if (check_key_val(key, value, flag, envs) != 0)
	{
		if (key[0] && is_valid_key(key))
		{
			creat_node(envs, key, value);
			g_exit_status = 0;
		}
		else
		{
			if (value)
			{
				error_cmd = ft_strjoin(key, "=");
				full_err = ft_strjoin(error_cmd, value);
				free(error_cmd);
				export_error(full_err, "not a valid identifier");
				free(full_err);
			}
			else
				export_error(key, "not a valid identifier");
		}
	}
}

void	add_export(char *cmd, t_envs **envs, int flag)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != '+')
		i++;
	if (i != ft_strlen(cmd))
	{
		if (cmd[i + 1] == '\0' || (cmd[i + 1] && (ft_isalnum(cmd[i + 1])
					|| cmd[i + 1] != '=')))
		{
			export_error(cmd, "not a valid identifier");
			return ;
		}
	}
	export_the_key_and_values(cmd, envs, flag);
}

void	set_export(char **cmds, t_envs **envs)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmds[i])
	{
		flag = is_append_or_add(cmds[i]);
		if (flag == 0 || flag == 2 || flag == 1)
			add_export(cmds[i], envs, flag);
		else
		{
			export_error(cmds[i], "not a valid identifier");
			g_exit_status = 1;
		}
		i++;
	}
}
