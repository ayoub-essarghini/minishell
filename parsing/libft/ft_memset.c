/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:37:27 by abbouram          #+#    #+#             */
/*   Updated: 2023/11/24 22:37:32 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cas;
	size_t			i;

	cas = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		cas[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
