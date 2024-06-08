/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:52:00 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 18:59:02 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_lst_size(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	close_pipes_in_parent(int (*pipefds)[2], int count)
{
	int	j;

	j = 0;
	while (j < count - 1)
	{
		close(pipefds[j][0]);
		close(pipefds[j][1]);
		j++;
	}
}

int	get_exit_status(int status)
{
	int	status2;
	int	term_signal;

	status2 = 0;
	if (WIFEXITED(status))
	{
		status2 = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		status2 = 128 + term_signal;
	}
	return (status2);
}

void	wait_for_children(int num_cmds, pid_t *pids)
{
	int	status;
	int	m;

	m = 0;
	while (m < num_cmds)
	{
		waitpid(pids[m], &status, 0);
		if (m == num_cmds - 1)
		{
			g_exit_status = get_exit_status(status);
		}
		m++;
	}
}
