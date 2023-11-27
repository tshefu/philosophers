/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:38 by vschneid          #+#    #+#             */
/*   Updated: 2023/11/27 20:19:15 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void input_error(t_table *table)
{
    (void)table;
    perror(KRED"Error");
    ft_putstr_fd("Wrong number of arguments!\n"KNRM, 2);
    exit(1);
}

void number_error(t_table *table)
{
    (void)table;
    perror(KRED"Error");
    ft_putstr_fd("Not all digit!\n"KNRM, 2);
    exit(1);
}

void negative_error(t_table *table)
{
    (void)table;
    perror(KRED"Error");
    ft_putstr_fd("Negative numbers not allowed"KNRM, 2);
    exit (1);
}