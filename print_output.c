/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:23:44 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/22 14:58:54 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_output(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (ft_strcmp(str, "died") == 0)
    {
        printf("%03ld %d %s\n", get_time(philo->table->start_time), philo->id, str);
        philo->table->some_philosopher_died = 1;
        pthread_mutex_unlock(&philo->table->print_lock);
        return ;
    }
    if (philo->table->some_philosopher_died)
    {
        pthread_mutex_unlock(&philo->table->print_lock);
        return ;
    }
    printf("%03ld %d %s\n", get_time(philo->table->start_time), philo->id, str);
    pthread_mutex_unlock(&philo->table->print_lock);
}
