/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:01:47 by dernst            #+#    #+#             */
/*   Updated: 2025/07/30 17:58:13 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo_die(t_data *data)
{
	pthread_mutex_lock(&data->mutex_die);
	if (data->philo_die == 1)
	{
		pthread_mutex_unlock(&data->mutex_die);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_die);
	return (0);
}

bool	check_death(t_philo *philo, unsigned long time_start)
{
	unsigned long time;

	time = current_time(time_start);
	if (time - philo->last_meal > philo->data->time_die)
	{
		philo->state = DIE;
		print(philo, DIE, time_start);
		pthread_mutex_lock(&philo->data->mutex_die);
		philo->data->philo_die = 1;
		pthread_mutex_unlock(&philo->data->mutex_die);
		return (1);
	}
	return (0);
}
