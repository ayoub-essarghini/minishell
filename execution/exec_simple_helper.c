/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:49:08 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 16:49:12 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	free_and_exit(char *full_cmd, char **args, int sv_in, int sv_out)
{
	command_404(args[0]);
	restore_redirections(sv_in, sv_out);
	exit(127);
}

int	exec_c(char **args, char **arr)
{
	if (execve(args[0], args, arr) == -1)
	{
		perror(args[0]);
		ft_freedouble(arr);
		return (-1);
	}
	if (arr)
		ft_freedouble(arr);
	return (0);
}

int	exec_with_path(char **args, t_envs *envs)
{
	char		**arr;
	struct stat	path_stat;

	arr = NULL;
	if (args && stat(args[0], &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_error(args[0], "Is a directory");
			ft_freedouble(arr);
			return (-1);
		}
		arr = convert_envs_to_arr(envs);
		return (exec_c(args, arr));
	}
	if (args[0] != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(args[0]);
	}
	return (2);
}

void	exec_not_bin(char **args, t_envs **envs, int sv_in, int sv_out)
{
	int	stt;

	stt = exec_with_path(args, *envs);
	if (stt == -1)
	{
		ft_freedouble(args);
		restore_redirections(sv_in, sv_out);
		exit(126);
	}
	else if (stt == 2)
	{
		ft_freedouble(args);
		restore_redirections(sv_in, sv_out);
		exit(127);
	}
	else
	{
		ft_freedouble(args);
		restore_redirections(sv_in, sv_out);
		exit(EXIT_SUCCESS);
	}
}

void	check_other_exec(char **args, t_envs **envs, int sv_in, int sv_out)
{
	if (args[0] && !ft_strchr(args[0], '/'))
	{
		command_404(args[0]);
		ft_freedouble(args);
		restore_redirections(sv_in, sv_out);
		exit(127);
	}
	else
		exec_not_bin(args, envs, sv_in, sv_out);
}
