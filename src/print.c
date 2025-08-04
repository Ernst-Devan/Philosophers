/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:50:48 by dernst            #+#    #+#             */
/*   Updated: 2025/07/23 17:32:00 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <threads.h>
#include <stdio.h>

unsigned int	print(t_philo *philo, enum e_state state, unsigned long time_start)
{
	unsigned long	time;


	pthread_mutex_lock(&philo->data->mutex_printf);
	time = current_time(time_start);
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
	printf("%lu %d", time, philo->id);
	if (state == EAT)
		printf(" is eating\n");
	if (state == SLEEP)
		printf(" is sleeping\n");
	if (state == THINK)
		printf(" is thinking\n");
	if (state == FORK)
		printf(" has taken a fork\n");
	if (state == DIE)
		printf(" died\n");
	pthread_mutex_unlock(&philo->data->mutex_printf);
	return (0);
}
