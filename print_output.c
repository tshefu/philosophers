/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:23:44 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 02:19:45 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_output(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->table->print_lock);
    long timestamp = get_time(philo->table->start_time);
    if (strcmp(str, "died") == 0)
    {
        printf("%03ld %d %s\n", timestamp, philo->id, str);
        pthread_mutex_lock(&philo->table->death_lock);
        philo->table->some_philosopher_died = 1;
        pthread_mutex_unlock(&philo->table->death_lock);
        pthread_mutex_unlock(&philo->table->print_lock);
        return;
    }
    pthread_mutex_lock(&philo->table->death_lock);
    if (philo->table->some_philosopher_died)
    {
        pthread_mutex_unlock(&philo->table->death_lock);
        pthread_mutex_unlock(&philo->table->print_lock);
        return;
    }
    pthread_mutex_unlock(&philo->table->death_lock);
    printf("%03ld %d %s\n", timestamp, philo->id, str);
    pthread_mutex_unlock(&philo->table->print_lock);
}







