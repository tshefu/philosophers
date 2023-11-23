/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:45:46 by vschneid          #+#    #+#             */
/*   Updated: 2023/08/01 16:31:36 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*source;
	size_t	i;

	if (!src || !dst || n <= 0)
		return (0);
	dest = (char *) dst;
	source = (char *) src;
	i = 0;
	while (n != i)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
