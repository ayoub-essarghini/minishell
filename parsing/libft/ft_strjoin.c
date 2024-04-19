/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:50:49 by abbouram          #+#    #+#             */
/*   Updated: 2023/11/24 22:50:55 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	size_t	i;
	size_t	p;

	if (!s1 || !s2)
		return (NULL);
	c = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!c)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i <= ft_strlen(s1))
	{
		c[i] = s1[i];
		i++ ;
	}
	p = 0;
	while (s2[p] != '\0' && p <= ft_strlen(s2))
	{
		c[i] = s2[p];
		i++;
		p++;
	}
	c[i] = '\0';
	return (c);
}
