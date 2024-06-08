/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:40:37 by abbouram          #+#    #+#             */
/*   Updated: 2023/11/24 22:40:43 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ls;
	size_t	ld;
	size_t	c;
	size_t	d;

	if (!dst && !size)
		return (ft_strlen(src));
	ls = ft_strlen(src);
	ld = ft_strlen(dst);
	c = 0;
	d = 0;
	if (size < ld || size == 0)
		return (ls + size);
	while (src[d] != '\0' && (ld + c) < size - 1)
	{
		dst[ld + c] = src[d];
		d++;
		c++;
	}
	dst[ld + c] = '\0';
	return (ls + ld);
}
