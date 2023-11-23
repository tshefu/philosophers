/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:25:10 by vschneid          #+#    #+#             */
/*   Updated: 2023/11/23 18:35:15 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_table
{
	int		*philo;
	int		*starving;
	int		*eating;
	int		*sleeping;
}		t_table;

#endif 