/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 21:33:30 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    print_output(philo, "is thinking");
    ft_usleep(100, philo);
}

int oh_no_someone_dead(t_table *table)
{
    int i = 0; 
    while (i < table->num_philos)
    {
        if(did_philo_die(&table->philo[i]))
            return(1);
        i++; 
    }
    return(0);
}

int did_philo_die(t_philo *philo)
{ 
    pthread_mutex_lock(&philo->table->meals_lock); 
    if((get_time_in_ms() - philo->last_meal) >= philo->table->time_to_die)
    {
        print_output(philo, "died");
        pthread_mutex_lock(&philo->table->death_lock);
        philo->table->some_philosopher_died = 1;
        pthread_mutex_unlock(&philo->table->death_lock);
        pthread_mutex_unlock(&philo->table->meals_lock);
        return(1);
    }
    pthread_mutex_unlock(&philo->table->meals_lock);
    return(0); 
}

void munch(t_philo *philo)
{
    int all_full;
    int i;
    
    pthread_mutex_lock(&philo->table->meals_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->table->meals_lock);

    print_output(philo, "is eating");
    ft_usleep(philo->table->time_to_eat, philo);
    pthread_mutex_lock(&philo->table->meals_lock);
    philo->meals++;
    all_full = 1;
    i = 0;
    while (i < philo->table->num_philos)
    {
        if (philo->table->philo[i].meals < philo->table->min_meals)
        {
            all_full = 0;
            break;
        }
        i++;
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

void munch_and_be_polite(t_philo *philo)
{
    munch(philo);
    put_down_forks(philo);
}

void *philosopher_routine_main(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;
    while (1)
    {
        if (oh_no_someone_dead(table))
            break;
        if (philo->id % 2 == 0)
            pick_up_forks_even(philo);
        else
            pick_up_forks_odd(philo);
        if (oh_no_someone_dead(table))
            break;
        munch_and_be_polite(philo);
        if (oh_no_someone_dead(table))
            break;
        sleepytime(philo);
        if (oh_no_someone_dead(table))
            break;
        think(philo);
    }
    put_down_forks(philo);
    return NULL;
}







