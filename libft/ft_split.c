/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:35:00 by vschneid          #+#    #+#             */
/*   Updated: 2023/08/01 16:35:11 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

static int	wordsize(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word;
	char	**strs;
	int		size;
	int		j;

	i = 0;
	j = 0;
	word = count_word(s, c);
	strs = (char **)malloc((word + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	while (j < word)
	{
		while (s[i] == c)
			i++;
		size = wordsize(s, c, i);
		strs[j] = ft_substr(s, i, size);
		i = i + size;
		j++;
	}
	strs[j] = NULL;
	return (strs);
}
