/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:18 by vschneid          #+#    #+#             */
/*   Updated: 2023/11/27 20:18:27 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    check_for_chars(t_table *table, char *array)
{
    int i;

    i = 0;
    while ((array[i] == ' ' || array[i] == '\t') && array[i])
        i++;
    if (array[i] == '+')
        i++;
    if (array[i] == '-' || array[i] == '\0')
        // error 
    while (array[i])
    {
        if (!ft_isdigit(array[i]))
            number_error(table);
        i++;
    }
}

