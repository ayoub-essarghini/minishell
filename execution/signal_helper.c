/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:52:49 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 17:09:03 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	handle_doc_int(int signal)
{
	(void)signal;
	write(STDIN_FILENO, "\n", 1);
	g_exit_status = 130;
	exit(130);
}

void	herdoc_signal(void)
{
	signal(SIGINT, handle_doc_int);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child_int(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}
