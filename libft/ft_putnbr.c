/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:47:53 by abbouram          #+#    #+#             */
/*   Updated: 2024/01/03 23:20:04 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int			count;
	long long	nb;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		count += ft_putchar('-');
	}
	if (nb < 10)
	{
		count += ft_putchar(nb + '0');
	}
	else
	{
		count += ft_putnbr(nb / 10);
		count += ft_putnbr(nb % 10);
	}
	return (count);
}
