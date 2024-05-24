/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:38 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/24 22:28:46 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_error(void)
{
	ft_putstr_fd(KRED"Wrong number of arguments! 5 or 6 needed\n"KNRM, 2);
	return (1);
}

int	input_error(void)
{
	ft_putstr_fd(KRED"Wrong input!\
			\nNeed philos, time to die, to munch, to sleep (and min meals).\
			\nValues can't be zero.\n"KNRM, 2);
	return (1);
}

int	calloc_error(void)
{
	ft_putstr_fd(KRED"Failed to allocate memory!\n"KNRM, 2);
	return (1);
}

int	init_error(t_table *table)
{
	ft_putstr_fd(KRED"Failed to initialize shared table!\n"KNRM, 2);
	cleanup_table(table);
	free(table);
	return (1);
}
