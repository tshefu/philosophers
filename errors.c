/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:38 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/19 20:05:33 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int arg_error()
{
    ft_putstr_fd(KRED"Wrong number of arguments! 5 or 6 needed\n"KNRM, 2);
    return 1;
}

int input_error()
{
    ft_putstr_fd(KRED"Wrong input!\
            \nNeed philos, time to die, to eat, to sleep (and min meals).\
            \nValues can't be zero.\n"KNRM, 2);
    return 1;
}

int malloc_error()
{
    ft_putstr_fd(KRED"Failed to allocate memory!\n"KNRM, 2);
    return 1;
}

int init_error(t_table *table)
{
    ft_putstr_fd(KRED"Failed to initialize shared table!\n"KNRM, 2);
    destroy_shared_table(table);
    free(table);
    return 1;
}