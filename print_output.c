/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:23:44 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/21 20:22:55 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_output(t_philo *philo, char *str)
{
    // TODO: still need to print philo died message
    if (philo->table->some_philosopher_died)
        return;
    pthread_mutex_lock(&philo->table->print_lock);
    printf("%03ld %d %s\n", get_time(philo->table->start_time), philo->id, str);
    pthread_mutex_unlock(&philo->table->print_lock);
}