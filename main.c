/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:19 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/06 00:54:21 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_table *table;

    if (argc < 5 || argc > 6)
        return arg_error();
    if (!valid_input(argc, argv))
        return input_error();
    table = ft_calloc(1, sizeof(t_table));
    if (!table)
        return malloc_error();
    if (initialize_shared_table(table) != 0)
        return init_error(table);
    set_the_table(table, argc, argv);
    print_table(table);

    // Start your threads and simulation here

    destroy_shared_table(table);
    free(table);
    return 0;
}



