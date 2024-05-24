/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:27:48 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 22:29:26 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_error(t_table *table)
{
	cleanup_table(table);
	free(table);
	return (1);
}

int	forks_mutex_error(t_table *table, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->philo_threads);
	free(table->forks);
	free(table->philo);
	return (1);
}

int	meals_mutex_error(t_table *table)
{
	int	i;

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
