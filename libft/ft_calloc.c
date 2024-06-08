/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:48:29 by abbouram          #+#    #+#             */
/*   Updated: 2024/01/03 23:23:47 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*buf;

	buf = malloc(nmemb * size);
	if (!buf)
		return (NULL);
	ft_bzero(buf, nmemb * size);
	return (buf);
}
