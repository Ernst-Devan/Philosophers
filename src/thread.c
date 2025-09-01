/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:03:31 by dernst            #+#    #+#             */
/*   Updated: 2025/07/29 00:28:02 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"
#include <pthread.h>
#include <stdio.h>

int	launch_dinner(t_data *data, t_philo *philo)
{
	pthread_t	*threads;

	threads = malloc(data->nb_philo * sizeof(pthread_t));
	if (!threads)
		return (1);
	if (launch_threads(philo, threads) == 0)
	{
		set_ready(data);
		waiting_threads(philo, threads);
	}
	free(threads);
	return (0);
}

void	free_mutex(t_philo *philo)
{
	pthread_mutex_destroy(&philo->l_fork->mutex);
	pthread_mutex_destroy(&philo->r_fork->mutex);
	pthread_mutex_destroy(&philo->data->mutex_die);
	pthread_mutex_destroy(&philo->data->mutex_printf);
	pthread_mutex_destroy(&philo->data->mutex_eat);
	pthread_mutex_destroy(&philo->data->mutex_state);
}

int	waiting_threads(t_philo *philo, pthread_t *threads)
{
	unsigned int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (1);
		i++;
	}
	free_mutex(philo);
	return (0);
}

int	return_threads(t_philo *philo, pthread_t *threads, unsigned int nb_threads)
{
	unsigned int	i;

	i = 0;
	while (i < nb_threads)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	free_mutex(philo);
	return (0);
}

int	launch_threads(t_philo *philo, pthread_t *threads)
{
	unsigned int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, &routine, &philo[i]))
		{
			return_threads(philo, threads, i);
			return (1);
		}
		i++;
	}
	return (0);
}
