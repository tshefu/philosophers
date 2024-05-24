/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:27:02 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 22:29:16 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_mutex_error(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->meals_lock);
	pthread_mutex_destroy(&table->philo->data_lock);
	return (1);
}

int	thread_create_error(t_table *table, int i, int j)
{
	ft_putstr_fd(KRED"Failed to create thread(s)!\n"KNRM, 2);
	while (j < i)
	{
		pthread_join(table->philo[j].thread, NULL);
		j++;
	}
	return (1);
}

int	monitor_thread_error(t_table *table, int j)
{
	ft_putstr_fd(KRED"Failed to create monitor thread!\n"KNRM, 2);
	while (j < table->num_philos)
	{
		pthread_join(table->philo[j].thread, NULL);
		j++;
	}
	return (1);
}

int	data_mutex_error(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->meals_lock);
	pthread_mutex_destroy(&table->print_lock);
	return (1);
}

int	death_mutex_error(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->meals_lock);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	return (1);
}
