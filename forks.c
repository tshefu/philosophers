/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:57:52 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 21:53:58 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks_even(t_philo *philo, int *right_locked, int *left_locked)
{
	usleep(100);
	pthread_mutex_lock(philo->right_fork);
	*right_locked = 1;
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->some_philosopher_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		put_down_forks(philo, right_locked, left_locked);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	print_output(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	*left_locked = 1;
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->some_philosopher_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		put_down_forks(philo, right_locked, left_locked);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	print_output(philo, "has taken a fork");
}

void	pick_up_forks_odd(t_philo *philo, int *right_locked, int *left_locked)
{
	usleep(100);
	pthread_mutex_lock(philo->left_fork);
	*left_locked = 1;
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->some_philosopher_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		put_down_forks(philo, right_locked, left_locked);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	print_output(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	*right_locked = 1;
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->some_philosopher_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		put_down_forks(philo, right_locked, left_locked);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	print_output(philo, "has taken a fork");
}

void	put_down_forks(t_philo *philo, int *right_locked, int *left_locked)
{
	if (*right_locked)
	{
		pthread_mutex_unlock(philo->right_fork);
		*right_locked = 0;
	}
	if (*left_locked)
	{
		pthread_mutex_unlock(philo->left_fork);
		*left_locked = 0;
	}
}
