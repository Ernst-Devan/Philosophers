/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:06:24 by dernst            #+#    #+#             */
/*   Updated: 2025/07/23 15:15:09 by dernst           ###   ########.fr       */
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
	{
		usleep(50);
	}
	i = 0;
	while (i < philo->data->nb_eat)
	{
		go_think(philo, philo->data->time_start);
		go_eat(philo, philo->data->time_start);
		i++;
	}
	return (NULL);
}

int go_sleep(t_philo *philo, unsigned long time_start)
{
	philo->state = SLEEP;
	print(philo, SLEEP, time_start);
	ft_usleep(philo, philo->data->time_sleep, time_start);
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
	while (fork_available(philo) == 0)
		usleep(100);
	take_fork(philo, time_start);
	unlock_fork(philo);
	philo->state = EAT;
	print(philo, EAT, time_start);
	philo->last_meal = 0;
	ft_usleep(philo, philo->data->time_eat, time_start);
	lock_fork(philo);
	philo->l_fork->state = 0;
	philo->r_fork->state = 0;
	unlock_fork(philo);
	go_sleep(philo, time_start);
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
