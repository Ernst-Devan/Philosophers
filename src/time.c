/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:16:49 by dernst            #+#    #+#             */
/*   Updated: 2025/07/22 16:17:34 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

bool	ft_usleep(t_philo *philo, unsigned long time, unsigned long time_start)
{
	unsigned int i;

	i = 0;
	while (i < (time / 1000) / 5)
	{
		usleep(5 * 1000);
		pthread_mutex_lock(&philo->data->mutex_die);
		if (philo->data->philo_die == 1)
			return (1);
		pthread_mutex_unlock(&philo->data->mutex_die);
		if (philo->last_meal >= philo->data->time_die)
		{
			philo->state=  DIE;
			pthread_mutex_lock(&philo->data->mutex_die);
			philo->data->philo_die = 1;
			pthread_mutex_unlock(&philo->data->mutex_die);
			print(philo, DIE, time_start);
			return(1);
		}
		i++;
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
