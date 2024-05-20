/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:19 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 12:54:11 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_simulation(t_table *table) {
    pthread_t monitor_thread;

    // Start philosopher threads
    for (int i = 0; i < table->num_philos; i++) {
        if (pthread_create(&table->philo[i].thread, NULL, philosopher_routine, &table->philo[i]) != 0) {
            table->some_philosopher_died = 1;
            break;
        }
    }

    // Start monitor thread
    if (!table->some_philosopher_died) {
        if (pthread_create(&monitor_thread, NULL, monitor_routine, table) != 0) {
            table->some_philosopher_died = 1;
        }
    }

    // Wait for monitor thread to finish
    pthread_join(monitor_thread, NULL);

    // Wait for philosopher threads to finish
    for (int i = 0; i < table->num_philos; i++) {
        pthread_join(table->philo[i].thread, NULL);
    }

    return 0;
}





int main(int argc, char *argv[]) {
    t_table *table;

    if (argc < 5 || argc > 6)
        return arg_error();
    if (!valid_input(argc, argv))
        return input_error();
    table = calloc(1, sizeof(t_table));
    if (!table)
        return malloc_error();
    if (init_table(table, argc, argv) != 0)
        return init_error(table);
    if (init_philosophers(table) != 0)
        return init_error(table);
    table->start_time = get_time_in_ms();
    //print_table(table);

    if (start_simulation(table) != 0) {
        cleanup_table(table);
        free(table);
        return 1;
    }
    cleanup_table(table);
    free(table);
    return 0;
}



