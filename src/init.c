/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:17:57 by dernst            #+#    #+#             */
/*   Updated: 2025/07/23 18:27:12 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	init_data(t_data *data, char **argv, int argc)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]) * 1000;
	data->time_eat = ft_atoi(argv[3]) * 1000;
	data->time_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	data->state = WAIT;
	data->philo_die = 0;
	data->all_eat = 0;
	pthread_mutex_init(&data->mutex_state, NULL);
	pthread_mutex_init(&data->mutex_printf, NULL);
	pthread_mutex_init(&data->mutex_die, NULL);
	pthread_mutex_init(&data->mutex_eat, NULL);
}

int	invite_philosophers(t_data *data, t_philo **philo)
{
	unsigned int	i;
	*philo = malloc((data->nb_philo) * sizeof(t_philo));
	if (!(*philo))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].state = ALIVE;
		(*philo)[i].l_fork = NULL;
		(*philo)[i].r_fork = NULL;
		(*philo)[i].data = data;
		(*philo)[i].last_meal = 0;
		i++;
	}
	return (0);
}

int	set_table(unsigned int nb_philo, t_fork **fork)
{
	unsigned int	i;

	*fork = malloc(nb_philo * sizeof(t_fork));
	if (!(*fork))
		return (1);
	i = 0;
	while (i < nb_philo)
	{
		(*fork)[i].state = 0;
		pthread_mutex_init(&((*fork)[i].mutex), NULL);
		i++;
	}
	return (0);
}
