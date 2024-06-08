/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:54:21 by abbouram          #+#    #+#             */
/*   Updated: 2024/01/03 22:53:58 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned long nb, int base)
{
	int	count;

	count = 0;
	if (nb < 16)
	{
		if (nb < 10)
			count += ft_putchar(nb + 48);
		else
		{
			if (base == 1)
				count += ft_putchar(nb + 87);
			else
				count += ft_putchar(nb + 55);
		}
	}
	if (nb >= 16)
	{
		count += ft_putnbr_base(nb / 16, base);
		count += ft_putnbr_base(nb % 16, base);
	}
	return (count);
}

int	ft_handle_format(char c, va_list list)
{
	if (c == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(list, int)));
	else if (c == 'u')
		return (ft_put_unsigned(va_arg(list, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(list, char *)));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(list, unsigned int), 1));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(list, unsigned int), 2));
	else if (c == 'p')
	{
		ft_putstr("0x");
		return (2 + ft_putnbr_base(va_arg(list, unsigned long int), 1));
	}
	else if (c == '%')
	{
		return (ft_putchar('%'));
	}
	else
		return (ft_putchar(c));
	return (0);
}
