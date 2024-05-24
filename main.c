/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:19 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 12:57:17 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int join_threads_normal_mode(t_table *table, int i)
{
    while (i < table->num_philos)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
    return 0;
}

int start_dinnertime(t_table *table)
{
    pthread_t monitor_death_thread;
    pthread_t monitor_meals_thread;
    int i;

    table->init_failed = false;

    // Create philosopher threads
    for (i = 0; i < table->num_philos; i++)
    {
        if (pthread_create(&table->philo[i].thread, NULL, philosopher_routine_main, &table->philo[i]) != 0)
        {
            table->init_failed = true;
            break;
        }
    }
    if (table->init_failed)
        return thread_create_error(table, i, 0);

    // Create monitoring threads
    if (pthread_create(&monitor_death_thread, NULL, monitor_death, table) != 0)
        return monitor_thread_error(table, 0);
    if (pthread_create(&monitor_meals_thread, NULL, monitor_meals, table) != 0)
        return monitor_thread_error(table, 0);
    // Wait for monitoring threads to finish
    pthread_join(monitor_death_thread, NULL);
    pthread_join(monitor_meals_thread, NULL);
    
    // Wait for philosopher threads to finish
    return join_threads_normal_mode(table, 0);
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
        return (calloc_error());
    if (init_table(table, argc, argv) != 0 || init_philosophers(table) != 0)
        return (init_error(table));
    table->start_time = get_time_in_ms();
    if (table->num_philos == 1)
        single_philosopher_routine_main(table);
    else
    {
        if (start_dinnertime(table) != 0)
            return (simulation_error(table));
    }
    cleanup_table(table);
    free(table);
    return (0);
}
