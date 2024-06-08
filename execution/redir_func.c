/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:52:34 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 17:08:33 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	dup_in(int *fd)
{
	if (dup2(*fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		close(*fd);
		exit(EXIT_FAILURE);
	}
	close(*fd);
}

void	dup_out(int *fd)
{
	if (dup2(*fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 output");
		close(*fd);
		exit(EXIT_FAILURE);
	}
	close(*fd);
}

int	red_in(char *filename, int *fd)
{
	if (access(filename, R_OK) == 0)
	{
		*fd = open(filename, O_RDONLY);
		if (*fd < 0)
		{
			perror(filename);
			close(*fd);
			return (1);
		}
		dup_in(fd);
		return (0);
	}
	perror(filename);
	return (1);
}

int	red_out(char *filename, int *fd)
{
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		perror(filename);
		close(*fd);
		return (1);
	}
	dup_out(fd);
	return (0);
	return (1);
}

int	red_app(char *filename, int *fd)
{
	*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
	{
		perror(filename);
		close(*fd);
		return (1);
	}
	dup_out(fd);
	return (0);
	return (1);
}
