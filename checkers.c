/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:18 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/06 00:56:19 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool no_philos_or_no_numbers(const char *input)
{
    int i;

    i = 0;
    if (input[0] == '0')
        return true;
    while (input[i])
    {
        if (!ft_isdigit(input[i]))
            return true;
        i++;
    }
    return false;
}

bool valid_input(int argc, char **argv)
{
    int philos;
    int j;
    
    j = 1;
    philos = ft_atoi(argv[1]);
    if (philos > 200 || philos <= 0)
        return false;
    while (j < argc)
    {
        if (no_philos_or_no_numbers(argv[j]) != 0)
            return false;
        j++;
    }
    return true;
}


