/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:11:29 by dernst            #+#    #+#             */
/*   Updated: 2025/07/23 15:11:48 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

int check_ready(t_data *data)
{
	pthread_mutex_lock(&data->mutex_state);
	if (data->state == 1)
	{
		pthread_mutex_unlock(&data->mutex_state);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_state);
	return (0);
}

void	set_ready(t_data *data)
{
	pthread_mutex_lock(&data->mutex_state);
	data->state = 1;
	data->time_start = get_time();
	pthread_mutex_unlock(&data->mutex_state);
	printf("Start Simulation !\n");
}
