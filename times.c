/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:01:48 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/22 22:05:06 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long microseconds)
{
    long start_time;
    long elapsed;
    
    start_time = get_time_in_ms();
    while (1)
    {
        elapsed = get_time_in_ms() - start_time;
        if (elapsed >= microseconds)
            break;
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