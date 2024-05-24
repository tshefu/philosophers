/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/25 01:39:32 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_dead_philo(t_table *table, int *left_locked, int *right_locked)
{
	pthread_mutex_lock(&table->death_lock);
	if (table->some_philosopher_died)
	{
		pthread_mutex_unlock(&table->death_lock);
		put_down_forks(table->philo, right_locked, left_locked);
		return (1);
	}
	pthread_mutex_unlock(&table->death_lock);
	return (0);
}

void	even_sleep_pre_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(4, philo->table);
}

void	*philosopher_routine_main(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int		right_locked;
	int		left_locked;

	philo = (t_philo *)arg;
	table = philo->table;
	right_locked = 0;
	left_locked = 0;
	even_sleep_pre_routine(philo);
	while (1)
	{
		if (check_for_dead_philo(table, &right_locked, &left_locked))
			break ;
		if (philo->id % 2 == 0)
			pick_up_forks_even(philo, &right_locked, &left_locked);
		else
			pick_up_forks_odd(philo, &right_locked, &left_locked);
		munch(philo);
		put_down_forks(philo, &right_locked, &left_locked);
		sleepytime(philo);
		think(philo);
	}
	put_down_forks(philo, &right_locked, &left_locked);
	return (NULL);
}
