/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:01:48 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/25 01:38:39 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long microseconds, t_table *table)
{
	long	start_time;
	long	elapsed;

	start_time = get_time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&table->philo->data_lock);
		elapsed = get_time_in_ms() - start_time;
		if (elapsed >= microseconds)
		{
			pthread_mutex_unlock(&table->philo->data_lock);
			break ;
		}
		usleep(100);
		pthread_mutex_unlock(&table->philo->data_lock);
	}
}

long	get_time(long start_time)
{
	return (get_time_in_ms() - start_time);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
