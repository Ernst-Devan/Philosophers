/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:36:07 by dernst            #+#    #+#             */
/*   Updated: 2025/06/30 12:54:44 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>
#include "philo.h"
#include "stdlib.h"
#include <stdio.h>

//dont accept number more than int max and negative number
// Number of philo musn't be 0 or negative or too high
// Destroy mutex at the end  !!!!!!!!!!!!!!!
// 
//
int	prepare_dinner(t_data *data, t_philo **philo, t_fork **fork)
{
	if (invite_philosophers(data, philo))
		return (1);
	if (set_table(data->nb_philo, fork))
		return (1);
	if (assign_fork(data, *philo, *fork))
		return (1);
	return (0);
}

bool	check_nb_philo(unsigned int nb)
{
	if (nb == 0)
	{
		printf(" 0 PHILO ????\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_fork		*fork;
	t_philo		*philo;

	if (check_args(argv, argc))
		return (1);
	init_data(&data, argv, argc);
	if (check_nb_philo(data.nb_philo))
		return (1);
	if (prepare_dinner(&data, &philo, &fork))
		return (1);
	if (launch_dinner(&data, philo))
		return (1);
	free(philo);
	free(fork);
	return (0);
}
