/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:50:48 by dernst            #+#    #+#             */
/*   Updated: 2025/08/07 16:09:48 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

unsigned int	print(t_philo *philo, enum e_state state,
					unsigned long start, char *msg)
{
	pthread_mutex_lock(&philo->data->mutex_printf);
	pthread_mutex_lock(&philo->data->mutex_die);
	if (philo->data->philo_die == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_die);
		pthread_mutex_unlock(&philo->data->mutex_printf);
		return (1);
	}
	else if (state == DIE)
		philo->data->philo_die = 1;
	pthread_mutex_unlock(&philo->data->mutex_die);
	printf("%lu %d %s", current_time(start), philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_printf);
	return (0);
}
