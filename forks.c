/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:57:52 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 00:55:10 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void pick_up_forks_even(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    print_output(philo, "has taken a fork");
    pthread_mutex_lock(philo->left_fork);
    print_output(philo, "has taken a fork");
}

void pick_up_forks_odd(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_output(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_output(philo, "has taken a fork");
}

/* void pick_up_forks_even(t_philo *philo)
{
    while (1)
    {
        pthread_mutex_lock(&philo->table->meals_lock);
        if ((get_time_in_ms() - philo->last_meal) >= philo->table->time_to_die)
        {
            pthread_mutex_unlock(&philo->table->meals_lock);
            return;
        }
        pthread_mutex_unlock(&philo->table->meals_lock);

        if (pthread_mutex_lock(philo->right_fork) == 0)
        {
            print_output(philo, "has taken a fork");
            if (pthread_mutex_lock(philo->left_fork) == 0)
            {
                print_output(philo, "has taken a fork");
                return;
            }
            pthread_mutex_unlock(philo->right_fork);
        }
        ft_usleep(200, philo); // Sleep for a short duration to yield control and avoid busy-waiting
    }
}

void pick_up_forks_odd(t_philo *philo)
{
    while (1)
    {
        pthread_mutex_lock(&philo->table->meals_lock);
        if ((get_time_in_ms() - philo->last_meal) >= philo->table->time_to_die)
        {
            pthread_mutex_unlock(&philo->table->meals_lock);
            return;
        }
        pthread_mutex_unlock(&philo->table->meals_lock);

        if (pthread_mutex_lock(philo->left_fork) == 0)
        {
            print_output(philo, "has taken a fork");
            if (pthread_mutex_lock(philo->right_fork) == 0)
            {
                print_output(philo, "has taken a fork");
                return;
            }
            pthread_mutex_unlock(philo->left_fork);
        }
        ft_usleep(200, philo); // Sleep for a short duration to yield control and avoid busy-waiting
    }
} */


void put_down_forks(t_philo *philo)
{
    if ((philo->id % 2 != 0) || (philo->table->num_philos % 2 && philo->id == philo->table->num_philos))
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    }
    else
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
    
    
}