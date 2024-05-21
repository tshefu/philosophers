/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:25:10 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/21 18:04:45 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

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

typedef struct s_table t_table;

typedef struct s_philo {
    t_table *table;
    pthread_t thread;
    int id;
    long last_meal;
    int meals;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_table {
    pthread_t *philo_threads;
    pthread_mutex_t *forks;
    t_philo *philo;
    int num_philos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long some_philosopher_died;
    long min_meals;
    long start_time;
    pthread_mutex_t meals_lock;
    pthread_mutex_t print_lock;
} t_table;

// INITIALIZERS

int     init_table(t_table *table, int argc, char **argv);
int     init_philosophers(t_table *table);

// ERROR HANDLING

int     input_error();
int     arg_error();
int     malloc_error();
int     init_error(t_table *table);
int     simulation_error(t_table *table);
int     forks_mutex_error(t_table *table, int i);
int     meals_mutex_error(t_table *table);
int     print_mutex_error(t_table *table);

// CHECKERS

bool    valid_input(int argc, char **argv);
bool    no_philos_or_no_numbers(const char *input);

// DEBUGGING

void    print_table(t_table *table);
void    print_output(t_philo *philo, char *str);

// CLEANUP

void cleanup_table(t_table *table);

// UTILS

long    get_time_in_ms(void);
long    get_time(long start_time);
void    ft_usleep(long microseconds);

// FT_FUNCTIONS

void	ft_putstr_fd(char const *s, int fd);
int     ft_isdigit(int c);
size_t  ft_strlen(const char *str);
long    ft_atol(char *str);

// ROUTINES

int start_simulation(t_table *table);
void *philosopher_routine(void *arg);
void *monitor_routine(void *arg);
void single_philosopher_routine(t_table *table);
void *you_single_you_die(void *arg);

#endif 