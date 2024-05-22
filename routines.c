/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 00:00:57 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    print_output(philo, "is thinking");
}

void munch(t_philo *philo)
{
    if (philo->table->some_philosopher_died)
            return ;
    print_output(philo, "is eating");
    philo->last_meal = get_time_in_ms();
        ft_usleep(philo->table->time_to_eat);
    philo->meals++;
}

void sleepytime(t_philo *philo)
{
    if (philo->table->some_philosopher_died)
        return ;
    print_output(philo, "is sleeping");
        ft_usleep(philo->table->time_to_sleep);
}

void *philosopher_routine_main(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;
    int right_locked = 0;
    int left_locked = 0;

    while (1)
    {
        pthread_mutex_lock(&table->death_lock);
        if (table->some_philosopher_died)
        {
            pthread_mutex_unlock(&table->death_lock);
            break;
        }
        pthread_mutex_unlock(&table->death_lock);
        usleep(100);
        if (philo->id % 2 == 0)
            pick_up_forks_even(philo, &right_locked, &left_locked);
        else
            pick_up_forks_odd(philo, &right_locked, &left_locked);
        pthread_mutex_lock(&table->death_lock);
        if (table->some_philosopher_died)
        {
            pthread_mutex_unlock(&table->death_lock);
            put_down_forks(philo, &right_locked, &left_locked);
            break;
        }
        pthread_mutex_unlock(&table->death_lock);

        pthread_mutex_lock(&philo->data_lock);
        munch(philo);
        pthread_mutex_unlock(&philo->data_lock);

        put_down_forks(philo, &right_locked, &left_locked);

        pthread_mutex_lock(&table->death_lock);
        if (table->some_philosopher_died)
        {
            pthread_mutex_unlock(&table->death_lock);
            break;
        }
        pthread_mutex_unlock(&table->death_lock);

        sleepytime(philo);

        pthread_mutex_lock(&table->death_lock);
        if (table->some_philosopher_died)
        {
            pthread_mutex_unlock(&table->death_lock);
            break;
        }
        pthread_mutex_unlock(&table->death_lock);

        think(philo);
    }
    put_down_forks(philo, &right_locked, &left_locked);
    return NULL;
}



