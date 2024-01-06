/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:25:10 by vschneid          #+#    #+#             */
/*   Updated: 2023/12/01 18:46:55 by vschneid         ###   ########.fr       */
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

/*
	struct to save all the information from the input
*/
typedef struct s_table
{
	int		philosopher;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	char	**argv;
}		t_table;

/*
	STRUCT FOR EACH PHILOSOPHER
	id : unique identifier for philosopher
	thread : thread associated with this philosopher
	times_eaten : (optional) counter to track how many times the philosopher
	has eaten
	table : pointer to shared t_table structure. allows each philosopher to
	access shared data 
*/
typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				times_eaten;
	struct s_table	*table;
}	t_philosopher;

// ERROR MESSAGES

void	input_error(t_table *table);
void	arg_error(t_table *table);

// CHECKERS

void    input_check(int argc, char **argv);

#endif 