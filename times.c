/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:01:48 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 20:01:47 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_usleep(long duration, t_philo *philo)
{
    long start_time = get_time_in_ms();
    while (philo->last_meal < duration)
    {
        if (start_time + duration >= get_time_in_ms())
            return 0;
        if (philo->last_meal + philo->table->time_to_die >= get_time_in_ms())
            return 1;
        usleep(duration / 10);
    }
    return 0;
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