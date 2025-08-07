/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:06:24 by dernst            #+#    #+#             */
/*   Updated: 2025/08/07 14:56:10 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"
#include <pthread.h>

bool	enough_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_eat);
	if (philo->data->all_eat == philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->data->mutex_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_eat);
	return (0);
}

void	*routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	while (check_ready(philo->data) == 0)
		usleep(DEFAULT);
	if (philo->id % 2)
		usleep(DELAY);
	while (philo->data->nb_eat != 0 && !enough_eat(philo))
	{
		if (go_think(philo, philo->data->time_start))
			return (NULL);
		if (go_eat(philo, philo->data->time_start))
			return (NULL);
		usleep(DEFAULT);
	}
	return (NULL);
}

int	go_sleep(t_philo *philo, unsigned long time_start)
{
	if (print(philo, SLEEP, time_start))
		return (1);
	if (ft_usleep(philo, philo->data->time_sleep, time_start))
		return (1);
	return (0);
}

int	go_think(t_philo *philo, unsigned long time_start)
{
	if (print(philo, THINK, time_start))
		return (1);
	return (0);
}

int	go_eat(t_philo *philo, unsigned long time_start)
{
	if (fork_available(philo, time_start))
		return (1);
	if (print(philo, EAT, time_start))
		return (1);
	philo->last_meal = get_time();
	if (ft_usleep(philo, philo->data->time_eat, time_start))
		return (1);
	philo->nb_eat++;
	pthread_mutex_lock(&philo->data->mutex_eat);
	if (philo->nb_eat == philo->data->nb_eat)
		philo->data->all_eat += 1;
	pthread_mutex_unlock(&philo->data->mutex_eat);
	release_forks(philo);
	if (go_sleep(philo, time_start))
		return (1);
	return (0);
}
