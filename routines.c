/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 20:00:32 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    print_output(philo, "is thinking");
    // Optional: Add a short random delay to simulate thinking time more realistically
    if (ft_usleep(100, philo) == 1)
    {
        pthread_mutex_lock(&philo->table->death_lock);
        philo->table->some_philosopher_died = 1;
        pthread_mutex_unlock(&philo->table->death_lock);
    }
}


void munch(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->meals_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->table->meals_lock);

    print_output(philo, "is eating");
    if (ft_usleep(philo->table->time_to_eat, philo) == 1)
    {
        pthread_mutex_lock(&philo->table->death_lock);
        philo->table->some_philosopher_died = 1;
        pthread_mutex_unlock(&philo->table->death_lock);
    }
    pthread_mutex_lock(&philo->table->meals_lock);
    philo->meals++;
    int all_full = 1;
    for (int i = 0; i < philo->table->num_philos; i++)
    {
        if (philo->table->philo[i].meals < philo->table->min_meals)
        {
            all_full = 0;
            break;
        }
    }
    if (all_full)
    {
        pthread_mutex_lock(&philo->table->death_lock);
        philo->table->all_full = 1;
        pthread_mutex_unlock(&philo->table->death_lock);
    }
    pthread_mutex_unlock(&philo->table->meals_lock);
}






void sleepytime(t_philo *philo)
{
    print_output(philo, "is sleeping");
    if (ft_usleep(philo->table->time_to_sleep, philo) == 1)
    {
        pthread_mutex_lock(&philo->table->death_lock);
        philo->table->some_philosopher_died = 1;
        pthread_mutex_unlock(&philo->table->death_lock);
    }
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
    t_table *table = philo->table;
    int right_locked = 0;
    int left_locked = 0;

    while (1)
    {
        if (death_lock(table))
            break;

        if (philo->id % 2 == 0)
        {
            pick_up_forks_even(philo, &right_locked, &left_locked);
        }
        else
        {
            pick_up_forks_odd(philo, &right_locked, &left_locked);
        }

        if (death_lock(table))
        {
            put_down_forks(philo, &right_locked, &left_locked);
            break;
        }

        munch(philo);
        put_down_forks(philo, &right_locked, &left_locked);

        if (death_lock(table))
            break;

        sleepytime(philo);

        if (death_lock(table))
            break;

        think(philo);
    }
    put_down_forks(philo, &right_locked, &left_locked);
    return NULL;
}







