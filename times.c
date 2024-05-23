/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:01:48 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 21:06:05 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long max_duration, t_philo *philo)
{
    long start_time;
    
    start_time = get_time_in_ms();
    while((get_time_in_ms() - start_time) <= max_duration)
    {
        if(death_lock(philo->table))
            break ;
        usleep(50); 
    }
}

/* void ft_usleep(long max_duration)
{
    long start_time;
    long elapsed;
    
    start_time = get_time_in_ms();
    while (1)
    {
        elapsed = get_time_in_ms() - start_time;
        if (elapsed >= max_duration)
            break;
        usleep(50);
    }
} */


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