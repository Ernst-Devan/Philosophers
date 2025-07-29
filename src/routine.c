/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:06:24 by dernst            #+#    #+#             */
/*   Updated: 2025/07/29 00:38:52 by dernst           ###   ########lyon.fr   */
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
	while (i < philo->data->nb_eat)
	{
		go_think(philo, philo->data->time_start);
		if (go_eat(philo, philo->data->time_start))
			return (NULL);
		go_think(philo, philo->data->time_start);
		i++;
	}
	return (NULL);
}

int go_sleep(t_philo *philo, unsigned long time_start)
{
	philo->state = SLEEP;
	print(philo, SLEEP, time_start);
	if (ft_usleep(philo, philo->data->time_sleep, time_start))
		return (1);
	return (0);
}

int	go_think(t_philo *philo, unsigned long time_start)
{
	if (philo->state == THINK)
		return (1);
	print(philo, THINK, time_start);
	philo->state = THINK;
	return (0);
}

int go_eat(t_philo *philo, unsigned long time_start)
{
	fork_available(philo, time_start);
	philo->state = EAT;
	print(philo, EAT, time_start);
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

bool	check_philo_starvation(unsigned long int last_meal, unsigned int time_die)
{
	if (last_meal >= time_die)
		return (1);
	return (0);
}

int	death_come()
{
	return (0);
}
