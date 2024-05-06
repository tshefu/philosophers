/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_statements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:17:15 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/06 00:56:40 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_table(t_table *table)
{
    printf("Number of philosophers: %d\n", table->num_philosophers);
    printf("Time to die: %d\n", table->time_to_die);
    printf("Time to eat: %d\n", table->time_to_eat);
    printf("Time to sleep: %d\n", table->time_to_sleep);
    printf("Minimum meals: %d\n", table->min_meals);
}
