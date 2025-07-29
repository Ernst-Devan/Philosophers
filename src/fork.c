/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:32:38 by dernst            #+#    #+#             */
/*   Updated: 2025/07/29 00:38:29 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/types.h>

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

bool	is_even(unsigned int nb)
{
	if (nb % 2 == 0)
		return (1);
	return (0);
}

bool	take_r_fork(t_philo *philo, unsigned long time_start)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	if (philo->r_fork->state == 0)
	{
		print(philo, FORK, time_start);
		philo->r_fork->state = 1;
	}
	else
	{
		pthread_mutex_unlock(&philo->r_fork->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->r_fork->mutex);
	return (1);
}

bool	take_l_fork(t_philo *philo, unsigned long time_start)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	if (philo->l_fork->state == 0)
	{
		print(philo, FORK, time_start);
		philo->l_fork->state = 1;
	}
	else
	{
		pthread_mutex_unlock(&philo->l_fork->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->l_fork->mutex);
	return (1);
}

bool	choose_first_fork(t_philo *philo, unsigned long time_start)
{
	if (is_even(philo->id))
	{
		if (take_r_fork(philo, time_start))
			return (1);
	}
	else 
	{
		if (take_l_fork(philo, time_start))
			return (1);
	}
	return (0);
}

bool	choose_second_fork(t_philo *philo, unsigned long time_start)
{
	if (is_even(philo->id))
	{
		if (take_l_fork(philo, time_start))
			return (1);
	}
	else 
	{
		if (take_r_fork(philo, time_start))
			return (1);
	}
	return (0);
}

bool fork_available(t_philo *philo, unsigned long time_start)
{
	while (choose_first_fork(philo, time_start) == 0)
	{
		ft_usleep(philo, 100, time_start);
	}
	while (choose_second_fork(philo, time_start) == 0)
	{
		ft_usleep(philo, 100, time_start);
	}
	return (0);
}

