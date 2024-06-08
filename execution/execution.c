/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:49:26 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:49:29 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	close_and_wait(int num_cmds, pid_t *pids, int (*pipefds)[2])
{
	close_pipes_in_parent(pipefds, num_cmds);
	wait_for_children(num_cmds, pids);
}

void	apply_red(t_red *red, int *sv_in, int *sv_out)
{
	apply_redirections(red, *&sv_in, *&sv_out);
	restore_redirections(*sv_in, *sv_out);
}

void	exec_cmd(t_cmd **tabcmd, t_envs **envs)
{
	t_cmd	*tmp;
	int		sv_out;
	int		sv_in;

	tmp = *tabcmd;
	if (tmp->type == cmd)
	{
		if (tmp->tab[0] != NULL)
		{
			if (is_builtin(tmp->tab[0]) == 0)
			{
				if (apply_redirections(tmp->red, &sv_in, &sv_out) == 0)
					exec_builtin(tmp, tmp->tab, tmp->red, envs);
				restore_redirections(sv_in, sv_out);
			}
			else
				exec_non_builtin(tmp->tab, tmp->red, envs);
		}
		else
			apply_red(tmp->red, &sv_in, &sv_out);
	}
	else
		exec_with_pipeline(*tabcmd, envs);
}
