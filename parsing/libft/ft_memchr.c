/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:45:29 by abbouram          #+#    #+#             */
/*   Updated: 2023/11/24 22:45:32 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*data;

	i = 0;
	data = (unsigned char *)s;
	while (i < n)
	{
		if (data[i] == (unsigned char)c)
			return ((void *)(data + i));
		i++;
	}
	return (NULL);
}
