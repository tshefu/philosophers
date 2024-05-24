/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:42:48 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 22:33:28 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	size_t	total_size;
	void	*ptr;

	if (num_elements && SIZE_MAX / num_elements < element_size)
		return (NULL);
	total_size = num_elements * element_size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	if (ptr)
		ft_memset(ptr, 0, total_size);
	return (ptr);
}

int	ft_abs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}
