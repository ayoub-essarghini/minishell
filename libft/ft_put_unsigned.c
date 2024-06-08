/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:50:21 by abbouram          #+#    #+#             */
/*   Updated: 2024/01/03 22:56:12 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_unsigned(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb < 10)
	{
		count += ft_putchar(nb + 48);
	}
	else
	{
		count += ft_put_unsigned(nb / 10);
		count += ft_put_unsigned(nb % 10);
	}
	return (count);
}
