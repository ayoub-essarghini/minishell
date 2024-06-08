/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:29:42 by abbouram          #+#    #+#             */
/*   Updated: 2024/01/03 23:46:00 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_line(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_line(char *databuf, char *buf)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!databuf)
	{
		databuf = (char *)malloc(1 * sizeof(char));
		databuf[0] = '\0';
	}
	if (!databuf || !buf)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(databuf) + ft_strlen(buf)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (databuf)
		while (databuf[++i] != '\0')
			str[i] = databuf[i];
	while (buf[j] != '\0')
		str[i++] = buf[j++];
	str[ft_strlen(databuf) + ft_strlen(buf)] = '\0';
	free(databuf);
	return (str);
}
