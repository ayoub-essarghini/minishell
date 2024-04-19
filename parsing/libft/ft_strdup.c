/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:49:18 by abbouram          #+#    #+#             */
/*   Updated: 2023/11/24 22:49:23 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dub;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	dub = malloc(sizeof(char) * (len + 1));
	if (!dub)
		return (NULL);
	while (s[i])
	{
		dub[i] = s[i];
		i++;
	}
	dub[i] = '\0';
	return (dub);
}
