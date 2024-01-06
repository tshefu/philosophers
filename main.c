/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:19 by vschneid          #+#    #+#             */
/*   Updated: 2023/12/04 17:18:02 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
   t_table table;

    if (argc < 5 || argc > 5)
        arg_error(NULL);
    input_check(argc, argv);
    table.philosopher = ft_atoi(argv[1]);
    table.time_to_die = ft_atoi(argv[2]);
    table.time_to_eat = ft_atoi(argv[3]);
    table.time_to_sleep = ft_atoi(argv[4]);

    ft_printf("Number of philosophers: %d\n", table.philosopher);
    ft_printf("Time to die: %d\n", table.time_to_die);
    ft_printf("Time to eat: %d\n", table.time_to_eat);
    ft_printf("Time to sleep: %d\n", table.time_to_sleep);

   return 0;
}


