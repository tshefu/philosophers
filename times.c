/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:01:48 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 17:04:16 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long time_to_eat, t_philo *philo)
{
    long start_time;
    long elapsed;
    
    start_time = get_time_in_ms();
    while (1)
    {
        elapsed = get_time_in_ms() - start_time;
        if (elapsed >= time_to_eat)
            break;
        if (philo->last_meal > philo->table->time_to_die)
        {
            pthread_mutex_lock(&philo->table->death_lock);
            philo->table->some_philosopher_died = 1;
            pthread_mutex_unlock(&philo->table->death_lock);
        }
        usleep(50);
    }
}

long get_time(long start_time)
{
    return (get_time_in_ms() - start_time);
}

long get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}