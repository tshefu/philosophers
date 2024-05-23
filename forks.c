/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:57:52 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 21:25:12 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void pick_up_forks_even(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    if (philo->table->some_philosopher_died)
    {
        put_down_forks(philo);
        return;
    }
    print_output(philo, "has taken a fork");
    pthread_mutex_lock(philo->left_fork);
    if (philo->table->some_philosopher_died)
    {
        put_down_forks(philo);
        return;
    }
    print_output(philo, "has taken a fork");
}

void pick_up_forks_odd(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_output(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_output(philo, "has taken a fork");
}

void put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}