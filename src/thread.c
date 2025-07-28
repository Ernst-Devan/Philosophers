/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:03:31 by dernst            #+#    #+#             */
/*   Updated: 2025/07/23 15:15:10 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"
#include <stdio.h>

int	launch_dinner(t_data *data, t_philo *philo)
{
	pthread_t		*threads;

	threads = malloc(data->nb_philo * sizeof(pthread_t));
	if (!threads)
		return (1);
	launch_threads(philo, threads);
	set_ready(data);
	waiting_threads(data, threads);
	return (0);
}

int	waiting_threads(t_data *data, pthread_t *threads)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	launch_threads(t_philo *philo, pthread_t *threads)
{
	unsigned int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
