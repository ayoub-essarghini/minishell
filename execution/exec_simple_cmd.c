/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:48:43 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:48:47 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	exec_simple(char *full_cmd, char **args, t_envs *envs)
{
	char	**arr;
	int		res;

	arr = convert_envs_to_arr(envs);
	res = execve(full_cmd, args, arr);
	if (full_cmd)
		free(full_cmd);
	ft_freedouble(arr);
	return (res);
}

void	check_exec_res(int result, char *full_cmd, char **args,
		int (*svinout)[2])
{
	if (result == -1)
		free_and_exit(full_cmd, args, (*svinout)[0], (*svinout)[1]);
	if (full_cmd)
		free(full_cmd);
	if (args)
		ft_freedouble(args);
	exit(EXIT_SUCCESS);
}

void	child_proc(char **args, t_red *rd, t_envs **envs)
{
	int		exec_result;
	int		svinout[2];
	char	*full_cmd;

	child_signal();
	if (apply_redirections(rd, &svinout[0], &svinout[1]) == 0)
	{
		full_cmd = get_cmd_bin(args, envs);
		if (full_cmd)
		{
			exec_result = exec_simple(full_cmd, args, *envs);
			check_exec_res(exec_result, full_cmd, args, &svinout);
			restore_redirections(svinout[0], svinout[1]);
		}
		else
			check_other_exec(args, envs, svinout[0], svinout[1]);
	}
	else
	{
		restore_redirections(svinout[0], svinout[1]);
		exit(EXIT_FAILURE);
	}
}

int	parent_proc(int *pid)
{
	int	status;
	int	status2;
	int	term_signal;

	status2 = 0;
	waitpid(*pid, &status, 0);
	if ((((status) >> 8) & 0x0000ff))
		status2 = (((status) >> 8) & 0x0000ff);
	else if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		status2 = 128 + term_signal;
	}
	return (status2);
}

void	exec_non_builtin(char **args, t_red *rd, t_envs **envs)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_proc(args, rd, envs);
	else
		g_exit_status = parent_proc(&pid);
}
