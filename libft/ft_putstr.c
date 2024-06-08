/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:50:00 by abbouram          #+#    #+#             */
/*   Updated: 2024/01/03 23:24:58 by abbouram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	char	*s;
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (str)
		s = str;
	else
		s = "(null)";
	while (s[i] != '\0')
	{
		count += ft_putchar(s[i]);
		i++;
	}
	return (count);
}
