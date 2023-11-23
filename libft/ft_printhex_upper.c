/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex_upper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:25:43 by vschneid          #+#    #+#             */
/*   Updated: 2023/08/27 22:16:23 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex_len_upper(unsigned int number)
{
	int	count;

	count = 0;
	while (number != 0)
	{
		count++;
		number = number / 16;
	}
	return (count);
}

void	ft_puthex_upper(unsigned long long number)
{
	if (number >= 16)
	{
		ft_puthex_upper(number / 16);
		ft_puthex_upper(number % 16);
	}
	else
	{
		if (number <= 9)
			ft_putchar(number + '0');
		else
			ft_putchar(number - 10 + 65);
	}
}

int	ft_printhex_upper(unsigned long long number)
{
	if (number == 0)
		return (write(1, "0", 1));
	else
		ft_puthex_upper(number);
	return (ft_hex_len_upper(number));
}
