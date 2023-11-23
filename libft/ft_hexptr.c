/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:41:38 by vschneid          #+#    #+#             */
/*   Updated: 2023/08/27 22:19:31 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printf_strlen(unsigned long long num)
{
	int	i;

	i = 0;
	if (num <= 15)
		return (1);
	while (num != 0)
	{
		i++;
		num = num / 16;
	}
	return (i);
}

int	ft_hexptr(unsigned long long num)
{
	if (num == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	ft_putchar('0');
	ft_putchar('x');
	ft_printhex_lower(num);
	return (printf_strlen(num) + 2);
}
