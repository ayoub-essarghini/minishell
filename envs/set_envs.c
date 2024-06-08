/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:15 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:24:17 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_envs(char *envs[], t_envs **envs_lst)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envs[i] != NULL)
	{
		key = get_key(envs[i]);
		value = get_value(envs[i]);
		creat_node(envs_lst, key, value);
		free(key);
		free(value);
		i++;
	}
}

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*get_key(char *str)
{
	int		len;
	char	*word;

	len = 0;
	word = NULL;
	while (str[len] && str[len] != '=' && str[len] != '+')
		len++;
	word = ft_word(str, 0, len);
	return (word);
}

char	*get_value(char *str)
{
	size_t	i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	while (str[i + j])
		j++;
	value = malloc((j + 1) * sizeof(char));
	if (!value)
		printf("allocation error\n");
	ft_strncpy(value, str + i, j);
	value[j] = '\0';
	return (value);
}

void	set_defautl_env(t_envs **envs)
{
	char	*cwd;
	char	*full_cwd;
	char	*data[4];

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		full_cwd = ft_strjoin("PWD=", cwd);
		free(cwd);
		data[0] = full_cwd;
		data[1] = "SHLVL=1";
		data[2] = "_=/usr/bin/env";
		data[3] = NULL;
		set_envs(data, &*envs);
		free(full_cwd);
	}
	else
	{
		data[0] = "PWD=HAYDNULL";
		data[1] = "SHLVL=1";
		data[2] = "_=/usr/bin/env";
		data[3] = NULL;
		set_envs(data, &*envs);
	}
}
