/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:28:45 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 12:17:51 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int malloc_table(t_table *table)
{
    table->philo_threads = malloc(table->num_philos * sizeof(pthread_t));
    table->forks = malloc(table->num_philos * sizeof(pthread_mutex_t));
    table->philo = malloc(table->num_philos * sizeof(t_philo));

    if (!table->philo_threads || !table->forks || !table->philo) {
        free(table->philo_threads);
        free(table->forks);
        free(table->philo);
        return 1;
    }
    return 0;
}


int atol_numbers(t_table *table, int argc, char **argv)
{
    table->num_philos = ft_atol(argv[1]);
    table->time_to_die = ft_atol(argv[2]);
    table->time_to_eat = ft_atol(argv[3]);
    table->time_to_sleep = ft_atol(argv[4]);
    table->some_philosopher_died = 0;
    if (argc == 6)
        table->min_meals = atol(argv[5]);
    else
        table->min_meals = -1;
    if (table->num_philos == -1 || table->time_to_die == -1
        || table->time_to_eat == -1 || table->time_to_sleep == -1
        || (argc == 6 && table->min_meals == -1))
        return 1;
    return 0;
}

int init_table(t_table *table, int argc, char **argv) {
    int i;

    if (atol_numbers(table, argc, argv) != 0)
        return 1;
    if (malloc_table(table) != 0)
        return 1;

    for (i = 0; i < table->num_philos; i++) {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0) {
            while (--i >= 0)
                pthread_mutex_destroy(&table->forks[i]);
            free(table->philo_threads);
            free(table->forks);
            free(table->philo);
            return 1;
        }
    }

    // Initialize the meals_lock mutex
    if (pthread_mutex_init(&table->meals_lock, NULL) != 0) {
        for (i = 0; i < table->num_philos; i++) {
            pthread_mutex_destroy(&table->forks[i]);
        }
        free(table->philo_threads);
        free(table->forks);
        free(table->philo);
        return 1;
    }

    return 0;
}


int init_philosophers(t_table *table)
{
    for (int i = 0; i < table->num_philos; i++) {
        table->philo[i].id = i + 1;
        table->philo[i].table = table;
        table->philo[i].last_meal = get_time_in_ms();
        table->philo[i].meals = 0;
        table->philo[i].print_lock = &table->forks[0]; // Assuming you have a separate print mutex
        table->philo[i].left_fork = &table->forks[i];
        table->philo[i].right_fork = &table->forks[(i + 1) % table->num_philos];
    }
    return 0;
}


