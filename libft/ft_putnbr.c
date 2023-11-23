/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:04:18 by vschneid          #+#    #+#             */
/*   Updated: 2023/08/27 22:16:35 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(unsigned int num)
{
	int	i;

	i = 0;
	while (num != 0)
	{
		i++;
		num = num / 10;
	}
	return (i);
}

void	put_extended(long n)
{
	if (n < 10)
	{
		ft_putchar(n + 48);
		return ;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
	return ;
}

int	ft_putnbr(long long int n)
{
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (n < 0)
	{
		ft_putchar('-');
		put_extended(n * -1);
		return (ft_numlen(n * -1) + 1);
	}
	else
	{
		put_extended(n);
		return (ft_numlen(n));
	}
}
