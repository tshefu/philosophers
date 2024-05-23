/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 01:05:26 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    print_output(philo, "is thinking");
    //ft_usleep(100, philo);
    //usleep(100);
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
    if (table->some_philosopher_died)
    {
        pthread_mutex_unlock(&table->death_lock);
        return(1); 
    }
    pthread_mutex_unlock(&table->death_lock);
    return(0); 
}

int all_philos_full(t_table *table)
{
    int i;
    int all_full = 1;

    if (table->min_meals == -1)
        return (0);
    pthread_mutex_lock(&table->meals_lock);
    i = 0;
    while (i < table->num_philos)
    {
        if (table->philo[i].meals < table->min_meals)
        {
            all_full = 0;
            break;
        }
        i++;
    }
    if (all_full)
    {
        //pthread_mutex_lock(&table->death_lock);
        table->all_full = 1;
        //pthread_mutex_unlock(&table->death_lock);
    }
    pthread_mutex_unlock(&table->meals_lock);
    return all_full;
}


void munch_and_be_polite(t_philo *philo)
{
    munch(philo);
    put_down_forks(philo);
}

void *philosopher_routine_main(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;
    int i = 0; 
    if (philo->id % 2 == 0 )
      ft_usleep(table->time_to_eat, philo);  
    while (1)
    {
        if (oh_no_someone_dead(table) || all_philos_full(table))
            break;
        if ((philo->id % 2 != 0) || (table->num_philos % 2 && philo->id == table->num_philos))
        {
            pick_up_forks_odd(philo);
            //ft_usleep(200, philo);
        }
        else
        {  
            pick_up_forks_even(philo);
            //ft_usleep(200, philo);
        }
        if (oh_no_someone_dead(table) || all_philos_full(table))
            break;
        munch_and_be_polite(philo);
        if (oh_no_someone_dead(table) || all_philos_full(table))
            break;
        sleepytime(philo);
        if (oh_no_someone_dead(table) || all_philos_full(table))
            break;
        think(philo);
        i++; 
        if(table->time_to_sleep >= table->time_to_eat)
            usleep(1000 * (table->time_to_sleep - table->time_to_eat) + 150); 
        else 
            usleep(1000 * (table->time_to_eat - table->time_to_sleep) + 150);
    }
    put_down_forks(philo);
    return NULL;
}








