/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:51:43 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 18:54:58 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	create_pipes(int (*pipefds)[2], int count)
{
	int	j;

	j = 0;
	while (j < count - 1)
	{
		if (pipe(pipefds[j]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

void	execute_command(t_cmd *cmd, t_envs **envs, int (*svinout)[2])
{
	if (!cmd->tab[0])
		exit(EXIT_SUCCESS);
	if (is_builtin(cmd->tab[0]) == 0)
	{
		if (ft_strcmp(cmd->tab[0], "exit") == 0)
			handle_builtin_exit(cmd, envs, svinout);
		else
			handle_builtin(cmd, envs, svinout);
	}
	else
	{
		handle_external_cmd(cmd, envs, svinout);
	}
}

void	close_pipes(int num_cmds, int cmd_index, int (*pipefds)[2])
{
	int	l;

	l = 0;
	while (l < num_cmds - 1)
	{
		if (l != cmd_index && l != cmd_index - 1)
		{
			close(pipefds[l][0]);
			close(pipefds[l][1]);
		}
		l++;
	}
}

void	execute_child_process(t_cmd *tmp, t_envs **envs, int (*pipefds)[2],
		t_pipeinfo *info)
{
	int	svinout[2];

	child_signal();
	if (info->cmd_index > 0)
	{
		dup2(pipefds[info->cmd_index - 1][0], STDIN_FILENO);
		close(pipefds[info->cmd_index - 1][0]);
		close(pipefds[info->cmd_index - 1][1]);
	}
	if (info->cmd_index < info->num_cmds - 1)
	{
		dup2(pipefds[info->cmd_index][1], STDOUT_FILENO);
		close(pipefds[info->cmd_index][0]);
		close(pipefds[info->cmd_index][1]);
	}
	close_pipes(info->num_cmds, info->cmd_index, pipefds);
	if (apply_redirections(tmp->red, &svinout[0], &svinout[1]) == 0)
		execute_command(tmp, envs, &svinout);
	else
		exit(EXIT_FAILURE);
}

int	exec_with_pipeline(t_cmd *tab, t_envs **envs)
{
	pid_t		*pids;
	int			(*pipefds)[2];
	t_pipeinfo	info;
	t_cmd		*tmp;
	pid_t		pid;

	info.num_cmds = ft_lst_size(tab);
	init_pipes(&pipefds, info.num_cmds);
	pids = init_pids(info.num_cmds);
	tmp = tab;
	info.cmd_index = 0;
	while (info.cmd_index < info.num_cmds && tmp)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			execute_child_process(tmp, envs, pipefds, &info);
		pids[info.cmd_index] = pid;
		info.cmd_index++;
		tmp = tmp->next;
	}
	close_and_wait(info.num_cmds, pids, pipefds);
	free(pids);
	free(pipefds);
	return (0);
}
