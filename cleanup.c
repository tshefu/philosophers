/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:31:26 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 12:18:11 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_table(t_table *table) {
    for (int i = 0; i < table->num_philos; i++) {
        pthread_mutex_destroy(&table->forks[i]);
    }
    pthread_mutex_destroy(&table->meals_lock);
    free(table->forks);
    free(table->philo_threads);
    free(table->philo);
}
