/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:56:05 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/22 23:56:25 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void single_philosopher_routine_main(t_table *table)
{
    t_philo *philo;
    
    philo = &table->philo[0];
    pthread_create(&philo->thread, NULL, you_single_you_die, philo);
    pthread_join(philo->thread, NULL);
}