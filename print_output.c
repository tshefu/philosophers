/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:23:44 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/23 22:26:39 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_output(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if(!death_lock(philo->table))
    { 
        printf("%03ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, str);
        pthread_mutex_unlock(&philo->table->print_lock);
        return ; 
    }
    pthread_mutex_unlock(&philo->table->print_lock);
}






