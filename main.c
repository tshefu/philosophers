/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:19 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/21 18:09:33 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_simulation(t_table *table)
{
    pthread_t monitor_thread;
    int i;

    i = 0;
    monitor_thread = 0;
    while (i < table->num_philos)
    {
        if (pthread_create(&table->philo[i].thread, NULL, philosopher_routine,\
            &table->philo[i]) != 0) {
            table->some_philosopher_died = 1;
            break;
        }
        i++;
    }
    if (!table->some_philosopher_died)
    {
        if (pthread_create(&monitor_thread, NULL, monitor_routine, table) != 0)
            table->some_philosopher_died = 1;
    }
    if (monitor_thread != 0)
        pthread_join(monitor_thread, NULL);
    i = 0;
    while (i < table->num_philos)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    t_table *table;

    if (argc < 5 || argc > 6)
        return (arg_error());
    if (!valid_input(argc, argv))
        return (input_error());
    table = calloc(1, sizeof(t_table));
    if (!table)
        return (malloc_error());
    if (init_table(table, argc, argv) != 0 || init_philosophers(table) != 0)
        return (init_error(table));
    table->start_time = get_time_in_ms();
    if (table->num_philos == 1)
        single_philosopher_routine(table);
    else
    {
        if (start_simulation(table) != 0)
            return (simulation_error(table));
    }
    cleanup_table(table);
    free(table);
    return (0);
}
