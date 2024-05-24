/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:31:00 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/25 01:39:20 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_happened(t_table *table, int i)
{
	pthread_mutex_lock(&table->death_lock);
	table->some_philosopher_died = 1;
	pthread_mutex_unlock(&table->death_lock);
	print_output(&table->philo[i], "died");
	pthread_mutex_unlock(&table->philo[i].data_lock);
}

int	find_dead_philos(t_table *table, int i)
{
	long	since_last_eat;

	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philo[i].data_lock);
		since_last_eat = get_time_in_ms() - table->philo[i].last_meal;
		if (since_last_eat > table->time_to_die)
		{
			death_happened(table, i);
			return (1);
		}
		pthread_mutex_unlock(&table->philo[i].data_lock);
		i++;
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		if (find_dead_philos(table, i) == 1)
			return (NULL);
		pthread_mutex_lock(&table->death_lock);
		if (table->some_philosopher_died)
		{
			pthread_mutex_unlock(&table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&table->death_lock);
		ft_usleep(5, table);
	}
	return (NULL);
}
