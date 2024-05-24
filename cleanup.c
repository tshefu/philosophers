/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:31:26 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 21:47:59 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].data_lock);
		i++;
	}
	pthread_mutex_destroy(&table->meals_lock);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	free(table->forks);
	free(table->philo_threads);
	free(table->philo);
}
