/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:19 by vschneid          #+#    #+#             */
/*   Updated: 2023/12/01 18:47:03 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
   t_table table;

    if (argc < 5 || argc > 5)
        arg_error(NULL);
    input_check(argc, argv);
    table.philo = ft_atoi(argv[1]);
    table.starving = ft_atoi(argv[2]);
    table.eating = ft_atoi(argv[3]);
    table.sleeping = ft_atoi(argv[4]);

    ft_printf("Number of philosophers: %d\n", table.philo);
    ft_printf("Time to die: %d\n", table.starving);
    ft_printf("Time to eat: %d\n", table.eating);
    ft_printf("Time to sleep: %d\n", table.sleeping);

   return 0;
}


