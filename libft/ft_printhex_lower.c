/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex_lower.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:23:48 by vschneid          #+#    #+#             */
/*   Updated: 2023/08/27 22:16:08 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex_len_lower(unsigned int number)
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

void	ft_puthex_lower(unsigned long long number)
{
	if (number >= 16)
	{
		ft_puthex_lower(number / 16);
		ft_puthex_lower(number % 16);
	}
	else
	{
		if (number <= 9)
			ft_putchar(number + '0');
		else
			ft_putchar(number - 10 + 97);
	}
}

int	ft_printhex_lower(unsigned long long number)
{
	if (number == 0)
		return (write(1, "0", 1));
	else
		ft_puthex_lower(number);
	return (ft_hex_len_lower(number));
}
