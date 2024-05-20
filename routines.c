/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 13:00:16 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ROUTINES

/*
    THINK: MOSTLY INVLOVES WAITING OR PRINTING.
    PICK UP FORKS: ATTEMPT TO PICK UP BOTH LEFT AND RIGHT FORKS USING MUTEXES.
    EAT: IF BOTH FORKS ARE ACQUIRED, LOCK THEM, EAT FOR TIME_TO_EAT MILISCECONDS,
    RECORD THE MEAL TIME.
    PUT DOWN FORKS: RELEASE BOTH FORKS (UNLOCK MUTEXES).
    SLEEP: SLEEP FOR TIME_TO_SLEEP MILISECONDS.
    
    CHECK FOR STARVATION: CONTINUOUSLY MONITOR IF IT'S BEEN MORE THAN TIME_TO_DIE
    MILISECONDS SINCE THE LAST MEAL.
*/

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;

    while (!table->some_philosopher_died) {
        // Thinking
        printf("%03ld %d is thinking\n", get_relative_time(table->start_time), philo->id);
        if (table->some_philosopher_died) break;

        // Picking up forks
        pthread_mutex_lock(philo->left_fork);
        if (table->some_philosopher_died) {
            pthread_mutex_unlock(philo->left_fork);
            break;
        }
        printf("%03ld %d has taken a fork\n", get_relative_time(table->start_time), philo->id);

        pthread_mutex_lock(philo->right_fork);
        if (table->some_philosopher_died) {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            break;
        }
        printf("%03ld %d has taken a fork\n", get_relative_time(table->start_time), philo->id);

        // Eating
        printf(KGRN"%03ld %d is eating\n"KNRM, get_relative_time(table->start_time), philo->id);
        philo->last_meal = get_time_in_ms();
        for (int i = 0; i < table->time_to_eat * 1000; i += 1000) {
            if (table->some_philosopher_died) break;
            usleep(1000);
        }
        philo->meals++;

        // Check if philosopher has eaten enough times
        if (table->min_meals != -1 && philo->meals >= table->min_meals) {
            table->some_philosopher_died = 1;
        }

        // Put down forks
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        if (table->some_philosopher_died) break;

        // Sleeping
        printf("%03ld %d is sleeping\n", get_relative_time(table->start_time), philo->id);
        for (int i = 0; i < table->time_to_sleep * 1000; i += 1000) {
            if (table->some_philosopher_died) break;
            usleep(1000);
        }
    }

    return NULL;
}



void *monitor_routine(void *arg) {
    t_table *table = (t_table *)arg;
    while (!table->some_philosopher_died) {
        for (int i = 0; i < table->num_philos; i++) {
            long time_since_last_meal = get_time_in_ms() - table->philo[i].last_meal;
            if (time_since_last_meal > table->time_to_die) {
                printf(KRED"%03ld %d died\n"KNRM, get_relative_time(table->start_time), table->philo[i].id);
                table->some_philosopher_died = 1;
                return NULL; // Exit the monitor thread
            }
        }
        usleep(1000); // Check every millisecond
    }
    return NULL;
}



