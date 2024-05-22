/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:31:26 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/22 23:28:55 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_table(t_table *table)
{
    int i;
    for (i = 0; i < table->num_philos; i++)
    {
        pthread_mutex_destroy(&table->forks[i]);
        pthread_mutex_destroy(&table->philo[i].data_lock);
    }
    pthread_mutex_destroy(&table->meals_lock);
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->death_lock);
    free(table->forks);
    free(table->philo_threads);
    free(table->philo);
}
