/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:38 by vschneid          #+#    #+#             */
/*   Updated: 2023/12/01 18:47:41 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void arg_error(t_table *table)
{
    (void)table;
    perror(KRED"Error");
    ft_putstr_fd("Wrong number of arguments!\n"KNRM, 2);
    exit(1);
}

void input_error(t_table *table)
{
    (void)table;
    perror(KRED"Error");
    ft_putstr_fd("Wrong input!\n"KNRM, 2);
    exit(1);
}