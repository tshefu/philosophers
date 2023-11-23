/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:32:19 by vschneid          #+#    #+#             */
/*   Updated: 2023/08/27 22:16:16 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printf_controller(va_list args, const char var)
{
	int	c;

	c = 0;
	if (var == 'c')
		c += ft_putchar(va_arg(args, int));
	else if (var == 's')
		c += ft_putstr(va_arg(args, char *));
	else if (var == 'p')
		c += ft_hexptr(va_arg(args, long long));
	else if (var == 'd' || var == 'i')
		c += ft_putnbr(va_arg(args, int));
	else if (var == 'u')
		c += ft_putnbr(va_arg(args, unsigned int));
	else if (var == 'x')
		c += ft_printhex_lower(va_arg(args, unsigned int));
	else if (var == 'X')
		c += ft_printhex_upper(va_arg(args, unsigned int));
	else if (var == '%')
		c += ft_putchar('%');
	return (c);
}

int	ft_printf(const char *fmt, ...)
{
	int		i;
	int		returnvalue;
	va_list	args;

	i = 0;
	returnvalue = 0;
	va_start (args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			i++;
			returnvalue += printf_controller(args, fmt[i]);
			i++;
		}
		else
		{
			returnvalue += ft_putchar(fmt[i]);
			i++;
		}
	}
	va_end(args);
	return (returnvalue);
}
