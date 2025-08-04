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

unsigned int	assign_fork(t_data *data, t_philo *philo, t_fork *forks)
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

unsigned int take_r_fork(t_philo *philo, unsigned long time_start)
{
	if (check_death(philo, time_start))
	{
		kill_philo(philo, time_start);
		return (2);
	}
	if (check_philo_die(philo->data))
		return (2);
	pthread_mutex_lock(&philo->r_fork->mutex);
	if (philo->r_fork->state == 0)
	{
		if (print(philo, FORK, time_start))
		{
			pthread_mutex_unlock(&philo->r_fork->mutex);
			return (1);
		}
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

unsigned int take_l_fork(t_philo *philo, unsigned long time_start)
{
	if (check_death(philo, time_start))
	{
		kill_philo(philo, time_start);
		return (2);
	}
	if (check_philo_die(philo->data))
		return (2);
	pthread_mutex_lock(&philo->l_fork->mutex);
	if (philo->l_fork->state == 0)
	{
		if (print(philo, FORK, time_start))
		{
			pthread_mutex_unlock(&philo->l_fork->mutex);
			return (1);
		}
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

unsigned int  choose_first_fork(t_philo *philo, unsigned long time_start)
{
	if (philo->id % 2)
		return (take_r_fork(philo, time_start));
	else 
		 return (take_l_fork(philo, time_start));
}

bool	choose_second_fork(t_philo *philo, unsigned long time_start)
{
	if (philo->id % 2)
		return (take_l_fork(philo, time_start));
	else 
		return (take_r_fork(philo, time_start));
}

bool fork_available(t_philo *philo, unsigned long time_start)
{
	unsigned int	state;

	state = 0;
	while (state == 0)
	{
		state = choose_first_fork(philo, time_start);
		if (state == 2 || ft_usleep(philo, 100, time_start))
			return (1);
	}
	state = 0;
	while (state == 0)
	{
		state = choose_second_fork(philo, time_start);
		if (state == 2 || ft_usleep(philo, 100, time_start))
			return (1);
	if (check_philo_die(philo->data))
			return (1);
	}
	return (0);
}

