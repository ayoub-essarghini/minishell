/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:15 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 19:31:58 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int		g_exit_status;

void	setup_signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_exit_free(t_cmd *tabcmd, t_envs *envs)
{
	ft_free_tab_command(tabcmd);
	tabcmd = NULL;
	ft_free_env(envs);
	envs = NULL;
	rl_clear_history();
}

void	lunch(t_envs **envlist)
{
	t_cmd	*tabcmd;
	char	*cmd;

	cmd = NULL;
	tabcmd = NULL;
	while (1)
	{
		setup_signals();
		cmd = readline("minishell  ➜ ");
		if (!cmd)
		{
			ft_exit_free(tabcmd, *envlist);
			printf("exit\n");
			exit(0);
		}
		if (check_line(cmd))
		{
			if (ft_parse_line(cmd, &tabcmd, envlist) == 1)
				exec_cmd(&tabcmd, envlist);
			ft_free_tab_command(tabcmd);
			tabcmd = NULL;
		}
		cmd = NULL;
	}
}

int	main(int argc, char *argv[], char *envs[])
{
	t_envs	*envlist;

	envlist = NULL;
	g_exit_status = 0;
	set_envs_list(argc, argv, envs, &envlist);
	lunch(&envlist);
}
