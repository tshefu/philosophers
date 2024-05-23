/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:56:59 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 02:05:34 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    long time_since_last_meal;
    t_table *table;
    int i;
    
    table = (t_table *)arg;
    while (1)
    {
        i = 0;
        while (i < table->num_philos)
        {
            pthread_mutex_lock(&table->philo[i].data_lock);
            time_since_last_meal = get_time_in_ms() - table->philo[i].last_meal;
            if (time_since_last_meal > table->time_to_die)
            {
                pthread_mutex_lock(&table->death_lock);
                table->some_philosopher_died = 1;
                pthread_mutex_unlock(&table->death_lock);
                print_output(&table->philo[i], "died");
                pthread_mutex_unlock(&table->philo[i].data_lock);
                return NULL;
            }
            pthread_mutex_unlock(&table->philo[i].data_lock);
            i++;
        }
        pthread_mutex_lock(&table->death_lock);
        if (table->some_philosopher_died)
        {
            pthread_mutex_unlock(&table->death_lock);
            break;
        }
        pthread_mutex_unlock(&table->death_lock);
        ft_usleep(5);
    }
    return NULL;
}