/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:15:50 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:15:51 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_parse_redirections(t_list **list, t_red **red, t_envs **envs)
{
	t_list	*current;
	t_list	*new;

	new = NULL;
	current = *list;
	while (current)
	{
		if (check_redirections(current->token))
		{
			red_list_add(red, current->token, current->next->input);
			current = current->next->next;
		}
		else
		{
			creat_last(&new, current->input, current->token, current->status);
			current = current->next;
		}
	}
	return (new);
}

char	**check_env_doc(char *line, t_envs **envs)
{
	t_list	*temp;
	char	**arr;
	t_list	*new;

	temp = NULL;
	ft_split_words(&temp, line, 0);
	new = temp;
	while (new)
	{
		expand_env_doc(new, envs);
		new = new->next;
	}
	arr = convert_list_to_arr(temp);
	ft_free(temp);
	return (arr);
}

void	read_the_input(int fd, t_envs **envs, t_list *list)
{
	char	*line;
	char	**arr;
	int		i;

	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, list->next->input) == 0)
			break ;
		else
		{
			i = 0;
			arr = check_env_doc(line, envs);
			while (arr[i])
			{
				ft_putstr_fd(arr[i], fd);
				i++;
			}
			write(fd, "\n", 1);
			ft_freedouble(arr);
		}
		free(line);
		line = readline("> ");
	}
	free(line);
}

void	here_doc_child(t_list *list, t_envs **envs, char *fd_name)
{
	int	fd;

	herdoc_signal();
	fd = open(fd_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	read_the_input(fd, envs, list);
	close(fd);
	exit(EXIT_SUCCESS);
}

int	parse_here_doc(t_list *list, t_envs **envs)
{
	pid_t	pid;
	int		status;
	char	*fd_name;

	fd_name = creat_name_heredoc();
	status = -1;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		here_doc_child(list, envs, fd_name);
	else
	{
		status = parent_proc(&pid);
		free(list->next->input);
		list->next->input = ft_strdup(fd_name);
		list->token = REDIR_IN;
		if (fd_name)
			free(fd_name);
	}
	return (status);
}
