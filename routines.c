/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 20:01:28 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    printf("%03ld %d is thinking\n", get_time(philo->table->start_time), philo->id);
}

void pick_forks_even(t_philo *philo)
{
    while (pthread_mutex_trylock(philo->right_fork) != 0)
    {
            if (philo->table->some_philosopher_died)
                return;
            ft_usleep(1000);
    }
    if (philo->table->some_philosopher_died) {
        pthread_mutex_unlock(philo->right_fork);
        return;
    }
    pthread_mutex_lock(&philo->table->print_lock);
    printf("%03ld %d has taken a fork\n", get_time(philo->table->start_time), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);

    while (pthread_mutex_trylock(philo->left_fork) != 0)
    {
        if (philo->table->some_philosopher_died) {
            pthread_mutex_unlock(philo->right_fork);
            return;
        }
        ft_usleep(1000);
    }
    if (philo->table->some_philosopher_died)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return;
    }
    pthread_mutex_lock(&philo->table->print_lock);
    printf("%03ld %d has taken a fork\n", get_time(philo->table->start_time), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
}

void pick_up_forks_odd(t_philo *philo)
{
    while (pthread_mutex_trylock(philo->left_fork) != 0)
    {
        if (philo->table->some_philosopher_died)
            return;
        ft_usleep(1000);
    }
    if (philo->table->some_philosopher_died)
    {
        pthread_mutex_unlock(philo->left_fork);
            return;
    }
    pthread_mutex_lock(&philo->table->print_lock);
    printf("%03ld %d has taken a fork\n", get_time(philo->table->start_time), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    while (pthread_mutex_trylock(philo->right_fork) != 0)
    {
        if (philo->table->some_philosopher_died)
        {
            pthread_mutex_unlock(philo->left_fork);
            return;
        }
        ft_usleep(1000);
    }
    if (philo->table->some_philosopher_died)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    pthread_mutex_lock(&philo->table->print_lock);
    printf("%03ld %d has taken a fork\n", get_time(philo->table->start_time), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
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
    pthread_mutex_lock(&philo->table->print_lock);
    printf("%03ld %d is eating\n", get_time(philo->table->start_time), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);

    philo->last_meal = get_time_in_ms();
    while (i < philo->table->time_to_eat * 1000)
    {
        if (philo->table->some_philosopher_died)
            return ;
        ft_usleep(1000);
        i += 1000;
    }
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
    pthread_mutex_lock(&philo->table->print_lock);
    printf("%03ld %d is sleeping\n", get_time(philo->table->start_time), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);

    while (i < philo->table->time_to_sleep * 1000)
    {
        if (philo->table->some_philosopher_died)
            return ;
        ft_usleep(1000);
        i += 1000;
    }
}


void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;

    while (!table->some_philosopher_died)
    {
        if (table->some_philosopher_died)
            break;
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

/**
 * Monitors the philosophers and checks if any of them have exceeded the time to die.
 * If a philosopher has exceeded the time to die, it prints a death message and sets
 * the flag `some_philosopher_died` to 1.
 * This function is meant to be run in a separate thread.
 *
 * @param arg A pointer to the `t_table` struct representing the dining table.
 * @return NULL
 */
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
                pthread_mutex_lock(&table->print_lock);
                printf("%03ld %d died\n", get_time(table->start_time), table->philo[i].id);
                pthread_mutex_unlock(&table->print_lock);
                table->some_philosopher_died = 1;
                return NULL;
            }
        }
        ft_usleep(500);
    }
    return NULL;
}

/**
 * Executes the routine for a single philosopher.
 *
 * @param table The table containing the philosophers.
 */
void single_philosopher_routine(t_table *table)
{
    t_philo *philo;

    philo = &table->philo[0];
    ft_usleep(table->time_to_die * 1000);
    pthread_mutex_lock(&table->print_lock);
    printf("%03ld %d died\n", get_time(table->start_time), philo->id);
    pthread_mutex_unlock(&table->print_lock);
}



