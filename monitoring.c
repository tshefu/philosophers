/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:56:59 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 17:08:58 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_death(void *arg)
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
        ft_usleep(5, table->philo);
    }
    return NULL;
}

/* void *monitor_meals(void *arg)
{
    t_table *table;
    int all_full;
    
    table = (t_table *)arg;
    while (1)
    {
        all_full = 1;
        for (int i = 0; i < table->num_philos; i++)
        {
            pthread_mutex_lock(&table->meals_lock);
            if (table->philo[i].meals < table->min_meals)
                all_full = 0;
            pthread_mutex_unlock(&table->meals_lock);
        }
        if (all_full)
        {
            pthread_mutex_lock(&table->death_lock);
            table->all_full = 1;
            //table->some_philosopher_died = 1;
            pthread_mutex_unlock(&table->death_lock);
            break;
        }
        ft_usleep(5, table->philo);
    }
    return NULL;
} */
