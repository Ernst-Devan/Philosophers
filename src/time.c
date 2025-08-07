/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:16:49 by dernst            #+#    #+#             */
/*   Updated: 2025/08/07 15:57:14 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

bool	ft_usleep(t_philo *philo, unsigned long sleep,
				unsigned long start)
{
	unsigned long	initial;

	initial = get_time() + sleep;
	while (get_time() < initial)
	{
		pthread_mutex_lock(&philo->data->mutex_die);
		if (philo->data->philo_die == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex_die);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mutex_die);
		if (check_death(philo, start))
			return (1);
		usleep(DEFAULT);
	}
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned long	current_time(unsigned long time_start)
{
	unsigned long	simulation_time;

	simulation_time = get_time() - time_start;
	return (simulation_time);
}
