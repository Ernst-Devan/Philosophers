/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:32:38 by dernst            #+#    #+#             */
/*   Updated: 2025/08/07 14:54:12 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/types.h>

unsigned int	assign_fork(t_data *data, t_philo *philo, t_fork *forks)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[data->nb_philo - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
	return (0);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->state = 0;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->state = 0;
	pthread_mutex_unlock(&philo->r_fork->mutex);
}

unsigned int	take_fork(t_philo *philo, t_fork *fork,
						unsigned long time_start)
{
	while (1)
	{
		if (check_death(philo, time_start))
			return (1);
		pthread_mutex_lock(&fork->mutex);
		if (fork->state == 0)
		{
			if (print(philo, FORK, time_start))
			{
				pthread_mutex_unlock(&fork->mutex);
				return (1);
			}
			fork->state = 1;
			pthread_mutex_unlock(&fork->mutex);
			return (0);
		}
		pthread_mutex_unlock(&fork->mutex);
		usleep(DEFAULT);
	}
}

bool	choose_forks(t_philo *philo, unsigned long time_start)
{
	if (philo->id % 2)
	{
		if (take_fork(philo, philo->r_fork, time_start))
			return (DEAD);
		if (take_fork(philo, philo->l_fork, time_start))
			return (DEAD);
	}
	else
	{
		if (take_fork(philo, philo->l_fork, time_start))
			return (DEAD);
		if (take_fork(philo, philo->r_fork, time_start))
			return (DEAD);
	}
	return (0);
}

bool	fork_available(t_philo *philo, unsigned long time_start)
{
	if (choose_forks(philo, time_start))
		return (DEAD);
	return (0);
}
