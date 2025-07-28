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
//dont accept number more than int max and negative number
// Number of philo musn't be 0 or negative or too high

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

int	main(int argc, char **argv)
{
	t_data		data;
	t_fork		*fork;
	t_philo		*philo;

	if (check_args(argc))
		return (1);
	init_data(&data, argv, argc);
	//Check the value of each args and chose if it's valid or not like nb_philo musn't be negative or null
	if (prepare_dinner(&data, &philo, &fork))
		return (1);
	if (launch_dinner(&data, philo))
		return (1);
	free(philo);
	free(fork);
	return (0);
}
