/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:25:10 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/08 10:41:46 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

# define MAXINPUT 100

// COLORS //

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

typedef struct s_table {
    pthread_mutex_t print_lock;  // Mutex for synchronizing output.
    int     num_philosophers;        // Total number of philosophers.
    long    time_to_die;             // Maximum time without eating before dying.
    long    time_to_eat;             // Time it takes for a philosopher to eat.
    long    time_to_sleep;           // Time a philosopher spends sleeping.
    long    some_philosopher_died;   // Flag to stop the simulation if a philosopher dies.
    long    min_meals;               // Minimum number of meals each philosopher must eat (optional).
} t_table;

// INITIALIZERS

int     initialize_shared_table(t_table *table);
void    set_the_table(t_table *table, int argc, char **argv);

// ERROR MESSAGES

int     input_error();
int     arg_error();
int     malloc_error();
int     init_error(t_table *table);

// CHECKERS

bool    valid_input(int argc, char **argv);
bool    no_philos_or_no_numbers(const char *input);

// DEBUGGING

void    print_table(t_table *table);

// CLEANUP

void    destroy_shared_table(t_table *table);

#endif 