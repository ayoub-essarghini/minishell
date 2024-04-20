/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:53:44 by abbouram          #+#    #+#             */
/*   Updated: 2023/11/24 22:53:47 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_digit(long num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		i++;
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	len;
	long	sign;
	char	*res;

	len = num_digit(n);
	sign = n;
	if (n < 0)
		sign *= -1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = 0;
	if (sign == 0)
		res[0] = '0';
	else
	{
		while (len--, sign != 0)
		{
			res[len] = (sign % 10) + '0';
			sign = (sign - (sign % 10)) / 10;
		}
		if (n < 0)
			res[len] = '-';
	}
	return (res);
}
