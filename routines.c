/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/21 20:17:36 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    print_output(philo, "is thinking");
}

void pick_forks_even(t_philo *philo)
{
    while (pthread_mutex_lock(philo->right_fork) != 0)
    {
        if (philo->table->some_philosopher_died)
            return;
        //ft_usleep(1000);
    }
    if (philo->table->some_philosopher_died) {
        pthread_mutex_unlock(philo->right_fork);
        return;
    }
    print_output(philo, "has taken a fork");
    while (pthread_mutex_lock(philo->left_fork) != 0)
    {
        if (philo->table->some_philosopher_died) {
            pthread_mutex_unlock(philo->right_fork);
            return;
        }
        //ft_usleep(1000);
    }
    if (philo->table->some_philosopher_died)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return;
    }
    print_output(philo, "has taken a fork");
}

void pick_up_forks_odd(t_philo *philo)
{
    while (pthread_mutex_lock(philo->left_fork) != 0)
    {
        if (philo->table->some_philosopher_died)
            return;
        //ft_usleep(1000);
    }
    if (philo->table->some_philosopher_died)
    {
        pthread_mutex_unlock(philo->left_fork);
            return;
    }
    print_output(philo, "has taken a fork");
    while (pthread_mutex_lock(philo->right_fork) != 0)
    {
        if (philo->table->some_philosopher_died)
        {
            pthread_mutex_unlock(philo->left_fork);
            return ;
        }
        //ft_usleep(1000);
    }
    if (philo->table->some_philosopher_died)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    print_output(philo, "has taken a fork");
}

void pick_up_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
        pick_forks_even(philo);
    else
        pick_up_forks_odd(philo);
}

void munch(t_philo *philo)
{
    int i;

    i = 0;
    print_output(philo, "is eating");
    philo->last_meal = get_time_in_ms();
    //while (i < philo->table->time_to_eat * 1000)
    //{
        if (philo->table->some_philosopher_died)
            return ;
        ft_usleep(philo->table->time_to_eat);
        //i += 1000;
    //}
    philo->meals++;
}


void put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void sleepytime(t_philo *philo)
{
    int i;

    i = 0;
    print_output(philo, "is sleeping");
    //while (i < philo->table->time_to_sleep)
    //{
        if (philo->table->some_philosopher_died)
            return ;
        ft_usleep(philo->table->time_to_sleep);
        //i += 1000;
    //}
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;

    while (!table->some_philosopher_died)
    {
        if (table->some_philosopher_died)
            break;
        usleep(100);
        pick_up_forks(philo);
        if (table->some_philosopher_died)
        {
            put_down_forks(philo);
            break;
        }
        munch(philo);
        if (table->some_philosopher_died)
        {
            put_down_forks(philo);
            break;
        }
        if (table->min_meals != -1 && philo->meals >= table->min_meals)
            table->some_philosopher_died = 1;
        put_down_forks(philo);
        if (table->some_philosopher_died)
            break;
        sleepytime(philo);
        if (table->some_philosopher_died)
            break;
        think(philo);
    }
    put_down_forks(philo);
    return NULL;
}

void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    while (!table->some_philosopher_died)
    {
        for (int i = 0; i < table->num_philos; i++)
        {
            long time_since_last_meal = get_time_in_ms() - table->philo[i].last_meal;
            if (time_since_last_meal > table->time_to_die)
            {
                print_output(&table->philo[i], "died");
                table->some_philosopher_died = 1;
                return NULL;
            }
        }
        ft_usleep(5);
    }
    return NULL;
}

void *you_single_you_die(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;
    pthread_mutex_lock(philo->left_fork);
    print_output(philo, "has taken a fork");
    ft_usleep(table->time_to_die);
    print_output(philo, "died");
    pthread_mutex_unlock(philo->left_fork);
    return NULL;
}

void single_philosopher_routine(t_table *table)
{
    t_philo *philo;
    
    philo = &table->philo[0];
    pthread_create(&philo->thread, NULL, you_single_you_die, philo);
    pthread_join(philo->thread, NULL);
}
