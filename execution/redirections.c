/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:52:18 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:52:21 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	handle_redirections(t_token type, char *filename, int *fd)
{
	int	status;

	if (type == REDIR_IN)
		status = red_in(filename, fd);
	else if (type == REDIR_OUT)
		status = red_out(filename, fd);
	else if (type == REDIR_APPEND)
		status = red_app(filename, fd);
	return (status);
}

void	restore_redirections(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	apply_redirections(t_red *rd, int *sv_in, int *sv_out)
{
	int	g_status;
	int	fd;

	*sv_in = dup(STDIN_FILENO);
	*sv_out = dup(STDOUT_FILENO);
	while (rd)
	{
		g_status = handle_redirections(rd->type, rd->input, &fd);
		if (g_status == 1)
		{
			g_exit_status = 1;
			return (-1);
		}
		else
			g_exit_status = 0;
		rd = rd->next;
	}
	return (0);
}
