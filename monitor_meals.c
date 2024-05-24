/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_meals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:56:59 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/25 01:39:25 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_satisfied(t_table *table)
{
	pthread_mutex_lock(&table->death_lock);
	table->some_philosopher_died = 1;
	table->all_full = 1;
	pthread_mutex_unlock(&table->death_lock);
}

void	check_meals(t_table *table, int *all_full)
{
	int	i;

	*all_full = 1;
	pthread_mutex_lock(&table->meals_lock);
	i = 0;
	while (i < table->num_philos)
	{
		if (table->philo[i].meals < table->min_meals)
		{
			*all_full = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&table->meals_lock);
}

void	*monitor_meals(void *arg)
{
	t_table	*table;
	int		all_full;

	table = (t_table *)arg;
	if (table->min_meals == -1)
		return (NULL);
	while (1)
	{
		check_meals(table, &all_full);
		pthread_mutex_lock(&table->death_lock);
		if (table->some_philosopher_died == 1)
		{
			pthread_mutex_unlock(&table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&table->death_lock);
		if (all_full == 1)
		{
			philos_satisfied(table);
			break ;
		}
		ft_usleep(5, table);
	}
	return (NULL);
}
