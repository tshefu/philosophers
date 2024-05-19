/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vschneid <vschneid@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:46:20 by vschneid          #+#    #+#             */
/*   Updated: 2024/05/08 10:49:34 by vschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ROUTINES

/*
    THINK: MOSTLY INVLOVES WAITING OR PRINTING.
    PICK UP FORKS: ATTEMPT TO PICK UP BOTH LEFT AND RIGHT FORKS USING MUTEXES.
    EAT: IF BOTH FORKS ARE ACQUIRED, LOCK THEM, EAT FOR TIME_TO_EAT MILISCECONDS,
    RECORD THE MEAL TIME.
    PUT DOWN FORKS: RELEASE BOTH FORKS (UNLOCK MUTEXES).
    SLEEP: SLEEP FOR TIME_TO_SLEEP MILISECONDS.
    
    CHECK FOR STARVATION: CONTINUOUSLY MONITOR IF IT'S BEEN MORE THAN TIME_TO_DIE
    MILISECONDS SINCE THE LAST MEAL.
*/