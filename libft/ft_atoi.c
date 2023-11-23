/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:45:45 by vschneid          #+#    #+#             */
/*   Updated: 2023/07/26 21:09:55 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	result;
	long	sign;
	int		c;

	c = 0;
	sign = 1;
	result = 0;
	while ((str[c] >= 9 && str[c] <= 13) || str[c] == 32)
		c++;
	while (str[c] == 43 || str[c] == 45)
	{
		if (str[c] == 45)
			sign *= -1;
		c++;
	}
	while (str[c] >= 48 && str[c] <= 57)
	{
		result = (str[c] -48) + (result * 10);
		c++;
	}
	return ((int)result * sign);
}
