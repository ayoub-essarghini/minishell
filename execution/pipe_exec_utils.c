/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:49:34 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 18:49:39 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	handle_builtin_exit(t_cmd *cmd, t_envs **envs, int (*svinout)[2])
{
	restore_redirections((*svinout)[0], (*svinout)[1]);
	ft_exit(cmd->tab, cmd, *envs, 0);
}

void	handle_builtin(t_cmd *cmd, t_envs **envs, int (*svinout)[2])
{
	exec_builtin(cmd, cmd->tab, cmd->red, envs);
	restore_redirections((*svinout)[0], (*svinout)[1]);
	exit(EXIT_SUCCESS);
}

void	handle_external_cmd(t_cmd *cmd, t_envs **envs, int (*svinout)[2])
{
	char	*full_cmd;
	int		exec_result;

	full_cmd = get_cmd_bin(cmd->tab, envs);
	if (full_cmd)
	{
		exec_result = exec_simple(full_cmd, cmd->tab, *envs);
		check_exec_res(exec_result, full_cmd, cmd->tab, svinout);
		restore_redirections((*svinout)[0], (*svinout)[1]);
	}
	else
	{
		check_other_exec(cmd->tab, envs, (*svinout)[0], (*svinout)[1]);
	}
}
