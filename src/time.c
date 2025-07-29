/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:16:49 by dernst            #+#    #+#             */
/*   Updated: 2025/07/29 00:54:49 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

bool	check_death(t_philo *philo, unsigned long time_start)
{
	unsigned long time;

	time = current_time(time_start);
	if (time - philo->last_meal > philo->data->time_die / 1000)
		return (1);
	return (0);
}

bool	ft_usleep(t_philo *philo, unsigned long time_sleep, unsigned long time_start)
{	
	unsigned long initial;
	(void)philo;

	initial = current_time(time_start);
	while (current_time(time_start) < initial + time_sleep / 1000)
	{
		usleep(100);
		if (check_death(philo, time_start))
		{
			philo->state = DIE;
			pthread_mutex_lock(&philo->data->mutex_die);
			if (philo->data->philo_die == 0)
				print(philo, DIE, time_start);
			philo->data->philo_die = 1;
			pthread_mutex_unlock(&philo->data->mutex_die);
			return (1);
		}
	}
	return (0);
}



unsigned long get_time()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned long	current_time(unsigned long time_start)
{
	unsigned long simulation_time;
	unsigned long current_time;

	current_time = get_time();
	simulation_time = current_time - time_start;
	return (simulation_time);
}
