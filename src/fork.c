/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:32:38 by dernst            #+#    #+#             */
/*   Updated: 2025/07/16 15:33:50 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	assign_fork(t_data *data, t_philo *philo, t_fork *forks)
{
	unsigned int i;

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

int fork_available(t_philo *philo)
{
	lock_fork(philo);
	if (philo->l_fork->state == 0 && philo->r_fork->state == 0)
	{
		return (1);
	}
	unlock_fork(philo);
	return (0);
}

int	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->r_fork->mutex);
	return (0);
}

int	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	return (0);
}

int	take_fork(t_philo *philo, unsigned long time_start)
{
	philo->l_fork->state = 1;
	print(philo, FORK, time_start);
	philo->r_fork->state = 1;
	print(philo, FORK, time_start);
	return (0);
}
