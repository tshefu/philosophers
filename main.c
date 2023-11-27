/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:19 by vschneid          #+#    #+#             */
/*   Updated: 2023/11/27 21:19:33 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int argv_len(char **argv)
{
    int i;

    i = 0;
    while (*argv)
    {
        argv++;
        i++;
    }
    return (i);
}

int main(int argc, char *argv[]) 
{
    t_table table;
    int len;
    int i;
    
    if (argc < 5 || argc > 5)
        input_error(NULL);

    i = 0;
    len = argv_len(argv);
    table.argv = argv;
    while (i < len)
    {
        check_for_chars(&table, argv[i]);
        i++;
    }

    table.philo = ft_atoi(argv[1]);
    table.starving = ft_atoi(argv[2]);
    table.eating = ft_atoi(argv[3]);
    table.sleeping = ft_atoi(argv[4]);

    ft_printf("Number of philosophers: %d\n", table.philo);
    ft_printf("Time to die: %d\n", table.starving);
    ft_printf("Time to eat: %d\n", table.eating);
    ft_printf("Time to sleep: %d\n", table.sleeping);
    
    return (0);
}
///////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXINPUT 100

int main(int argc, char **argv) {
   char input[MAXINPUT] = "";
   int length, i; 

   // Assuming argv[1] is the input
   strcpy(input, argv[1]);
   length = strlen(input);

   // Check if the input is positive
   if (input[0] == '0') {
       printf("Entered input is not a positive number\n");
       exit(1);
   }

   for (i=0; i<length; i++) {
       if (!isdigit(input[i])) {
           printf("Entered input is not a number\n");
           exit(1);
       }
   }
   printf("Given input is a positive number\n");
   return 0;
}
