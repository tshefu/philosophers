/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 17:07:30 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    print_output(philo, "is thinking");
}


void munch(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->meals_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->table->meals_lock);
    print_output(philo, "is eating");
    ft_usleep(philo->table->time_to_eat, philo);
    pthread_mutex_lock(&philo->table->meals_lock);
    philo->meals++;
    pthread_mutex_unlock(&philo->table->meals_lock);
}


void sleepytime(t_philo *philo)
{
    print_output(philo, "is sleeping");
    ft_usleep(philo->table->time_to_sleep, philo);
}

int death_lock(t_table *table)
{
    pthread_mutex_lock(&table->death_lock);
    if (table->some_philosopher_died) //|| table->all_full)
    {
        pthread_mutex_unlock(&table->death_lock);
        return(1); 
    }
    pthread_mutex_unlock(&table->death_lock);
    return(0); 
}

void *philosopher_routine_main(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int right_locked = 0;
    int left_locked = 0;

    while (!(death_lock(philo->table)))
    {
        if (philo->id % 2 == 0)
        {
            //ft_usleep(4);
            pick_up_forks_even(philo, &right_locked, &left_locked);
        }
        else
        {
            //ft_usleep(4);
            pick_up_forks_odd(philo, &right_locked, &left_locked);
        }
        munch(philo);
        put_down_forks(philo, &right_locked, &left_locked);
        sleepytime(philo);
        think(philo);
    }
    return NULL;
}


