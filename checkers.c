/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:18 by vschneid          #+#    #+#             */
/*   Updated: 2023/12/01 18:47:21 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    input_check(int argc, char **argv)
{
    char    input[MAXINPUT] = "";
    int     length;
    int     i;
    int     j;

    j = 1;
    while (j < argc)
    {
        ft_strcpy(input, argv[j]);
        length = ft_strlen(input);
        if (input[0] == '0')
            input_error(NULL);
        i = 0;
        while (i < length)
        {
            if (!ft_isdigit(input[i]))
                input_error(NULL);
            i++;
        }
        j++;
    }
}

