/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:52:18 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 22:19:05 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	init_pipes(int (**pipefds)[2], int num_cmds)
{
	*pipefds = malloc(sizeof(int [2]) * (num_cmds - 1));
	if (!*pipefds)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	create_pipes(*pipefds, num_cmds);
}

pid_t	*init_pids(int num_cmds)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (pids);
}
