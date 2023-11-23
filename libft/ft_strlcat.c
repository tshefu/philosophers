/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:45:47 by vschneid          #+#    #+#             */
/*   Updated: 2023/07/31 10:55:34 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (dest[j] && j < destsize)
		j++;
	while ((src[k]) && ((j + k + 1) < destsize))
	{
		dest[j + k] = src[k];
		k++;
	}
	if (j != destsize)
		dest[j + k] = '\0';
	return (j + ft_strlen(src));
}
