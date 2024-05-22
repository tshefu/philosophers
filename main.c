/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:19 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/22 23:55:05 by vschneid         ###   ########.fr       */
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
    pthread_t monitor_thread;
    int i;
    int j;

    i = 0;
    monitor_thread = 0;
    while (i < table->num_philos)
    {
        if (pthread_create(&table->philo[i].thread, NULL, philosopher_routine_main,\
            &table->philo[i]) != 0)
        {
            table->init_failed = true;
            break ;
        }
        i++;
    }
    j = 0;
    if (table->init_failed)
        return thread_create_error(table, i, j);
    if (pthread_create(&monitor_thread, NULL, monitor_routine, table) != 0)
        return monitor_thread_error(table, j);
    pthread_join(monitor_thread, NULL);
    i = 0;
    return join_threads_normal_mode(table, i);
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
