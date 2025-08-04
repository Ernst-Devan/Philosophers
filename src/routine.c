/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:06:24 by dernst            #+#    #+#             */
/*   Updated: 2025/07/30 18:16:44 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"
#include <pthread.h>

void	*routine(void *thread)
{
	t_philo *philo;
	unsigned int i;
	
	philo = (t_philo *)thread;
	while (check_ready(philo->data) == 0) 
		usleep(100);
	i = 0;
	if (philo->id % 2)
		usleep(25000);
	while (i < philo->data->nb_eat)
	{
		if (go_think(philo, philo->data->time_start))
			return (NULL);
		if (go_eat(philo, philo->data->time_start))
			return (NULL);
		if (go_think(philo, philo->data->time_start))
			return (NULL);
		usleep(100);
		i++;
	}
	return (NULL);
}

int go_sleep(t_philo *philo, unsigned long time_start)
{
	philo->state = SLEEP;
	if (print(philo, SLEEP, time_start))
		return (1);
	if (ft_usleep(philo, philo->data->time_sleep, time_start))
		return (1);
	return (0);
}

int	go_think(t_philo *philo, unsigned long time_start)
{
	pthread_mutex_lock(&philo->data->mutex_die);
	if (philo->data->philo_die)
	{
		pthread_mutex_unlock(&philo->data->mutex_die);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_die);
	if (philo->state == THINK)
		return (0);
	if (print(philo, THINK, time_start))
		return (1);
	philo->state = THINK;
	return (0);
}

int go_eat(t_philo *philo, unsigned long time_start)
{
	if (fork_available(philo, time_start))
		return (1);
	philo->state = EAT;
	if (print(philo, EAT, time_start))
		return (1);
	philo->last_meal = current_time(time_start);
	if (ft_usleep(philo, philo->data->time_eat, time_start))
		return (1);
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->state = 0;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->state = 0;
	pthread_mutex_unlock(&philo->r_fork->mutex);
	if (go_sleep(philo, time_start))
		return (1);
	return (0);
}

