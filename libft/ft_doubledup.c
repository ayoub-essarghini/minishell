/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubledup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:57:14 by abbouram          #+#    #+#             */
/*   Updated: 2024/06/05 22:57:16 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_doubledup(char **s)
{
	char	**dup;
	int		i;
	int		len1;

	i = 0;
	len1 = 0;
	while (s[len1])
		len1++;
	dup = (char **)malloc(sizeof(char *) * (len1 + 1));
	while (i < len1)
	{
		dup[i] = ft_strdup(s[i]);
		i++;
	}
	dup[len1] = NULL;
	return (dup);
}
