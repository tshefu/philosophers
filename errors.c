/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:38 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 17:29:06 by vschneid         ###   ########.fr       */
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
            \nNeed philos, time to die, to munch, to sleep (and min meals).\
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
    cleanup_table(table);
    free(table);
    return 1;
}

int simulation_error(t_table *table)
{
    cleanup_table(table);
    free(table);
    return 1;
}

int forks_mutex_error(t_table *table, int i)
{
    while (--i >= 0)
        pthread_mutex_destroy(&table->forks[i]);
    free(table->philo_threads);
    free(table->forks);
    free(table->philo);
    return (1);
}

int meals_mutex_error(t_table *table)
{
    int i;

    i = 0;
    while (i < table->num_philos)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->philo_threads);
    free(table->forks);
    free(table->philo);
    return (1);
}

int print_mutex_error(t_table *table)
{
    int i = 0;

    while (i < table->num_philos) {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&table->meals_lock);
    return 1;
}
