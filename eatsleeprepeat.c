/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleeprepeat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:29:55 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 22:30:38 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *phi)
{
	print_output(phi, "is thinking");
	if ((phi->id % 2)
		&& (phi->table->sleeptime != phi->table->eattime))
		usleep(ft_abs(phi->table->sleeptime
				- phi->table->eattime) * 1000 + 100);
}

void	munch(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->some_philosopher_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	print_output(philo, "is eating");
	pthread_mutex_lock(&philo->data_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data_lock);
	ft_usleep(philo->table->eattime);
	pthread_mutex_lock(&philo->table->meals_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->table->meals_lock);
}

void	sleepytime(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->some_philosopher_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	print_output(philo, "is sleeping");
	ft_usleep(philo->table->sleeptime);
}
