/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:28:45 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 08:54:36 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int initialize_shared_table(t_table *table)
{
    if (pthread_mutex_init(&table->print_lock, NULL) != 0)
        return -1;
    // Initialize other fields if needed
    return 0;
}

void set_the_table(t_table *table, int argc, char **argv)
{
    table->num_philosophers = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        table->min_meals = ft_atoi(argv[5]);
    else
        table->min_meals = 0;
}