/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_statements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:17:15 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/20 10:36:31 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_table(t_table *table)
{
    printf("Table Information:\n");
    printf("Number of Philosophers: %d\n", table->num_philos);
    printf("Time to Die: %ld ms\n", table->time_to_die);
    printf("Time to Eat: %ld ms\n", table->time_to_eat);
    printf("Time to Sleep: %ld ms\n", table->time_to_sleep);
    printf("Minimum Meals (optional): %ld\n", table->min_meals);
    printf("Some Philosopher Died: %ld\n", table->some_philosopher_died);

    for (int i = 0; i < table->num_philos; i++) {
        t_philo *philo = &table->philo[i];
        printf("\nPhilosopher %d:\n", philo->id);
        printf("ID: %d\n", philo->id);
        printf("Last Meal: %ld ms\n", philo->last_meal);
        printf("Meals: %d\n", philo->meals);
        printf("Print Lock: %p\n", (void *)philo->print_lock);
        printf("Left Fork: %p\n", (void *)philo->left_fork);
        printf("Right Fork: %p\n", (void *)philo->right_fork);
    }
    printf("\n");
}
