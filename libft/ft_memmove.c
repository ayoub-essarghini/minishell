/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:38:58 by abbouram          #+#    #+#             */
/*   Updated: 2023/11/24 22:39:04 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;
	size_t			i;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (cdest < csrc)
	{
		ft_memcpy(cdest, csrc, n);
	}
	if (cdest >= csrc)
	{
		i = n;
		while (i > 0)
		{
			i--;
			cdest[i] = csrc[i];
		}
	}
	return (dest);
}
