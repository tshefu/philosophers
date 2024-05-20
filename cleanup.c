/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:31:26 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 15:51:26 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Cleans up the resources used by the dining philosophers table.
 * 
 * This function destroys the mutexes used for the forks and the meals_lock,
 * and frees the memory allocated for the forks, philo_threads, and philo arrays.
 * 
 * @param table The dining philosophers table to be cleaned up.
 */
void cleanup_table(t_table *table)
{
    int i;

    i = 0;
    while (i < table->num_philos)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&table->meals_lock);
    free(table->forks);
    free(table->philo_threads);
    free(table->philo);
}
