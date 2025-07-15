/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:36:07 by dernst            #+#    #+#             */
/*   Updated: 2025/06/30 12:54:44 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "philo.h"
#include "stdlib.h"
#include "sys/time.h"

//dont accept number more than int max and negative number

void	display_settings(t_settings set)
{
	printf("nb_philo   : %d\n", set.nb_philo);
	printf("time_die   : %d\n", set.time_die);
	printf("time_eat   : %d\n", set.time_eat);
	printf("time_sleep : %d\n", set.time_sleep);
	printf("nb_eat     : %d\n", set.nb_eat);
}

int		ft_atoi(char *str)
{
	long int		nb;
	unsigned int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		nb *= 10;
		nb += str[i] -= '0';
		i++;
	}
	return (nb);
}

void	init_settings(t_settings *settings, char **argv, int argc)
{
	settings->nb_philo = ft_atoi(argv[1]);
	settings->time_die = ft_atoi(argv[2]);
	settings->time_eat = ft_atoi(argv[3]);
	settings->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		settings->nb_eat = ft_atoi(argv[5]);
	else
		settings->nb_eat = -1;
}

unsigned int	check_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			printf("Not enough args\n");
		if (argc > 6)
			printf("Too many args\n");
		return (1);
	}
	return (0);
}

void	display_philo(t_philo *philo, unsigned int nb_philo)
{
	unsigned int	i;

	i = 0;
	printf("\n\n");
	while (i < nb_philo)
	{
		printf("-------------\n");
		printf("Philo : %d\n", philo[i].id);
		printf("State : %d\n", philo[i].state);
		//printf("Left  : %d\n", philo[i].l_fork);
		//printf("Right : %d\n", philo[i].r_fork);
		i++;
	}
	printf("-------------\n");
	printf("\n\n");
}

int	invite_philosophers(t_settings set, t_philo **philo)
{
	unsigned int	i;
	*philo = malloc((set.nb_philo + 1) * sizeof(t_philo));
	if (!philo)
		return (1);
	i = 0;
	while (i < set.nb_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].state = THINK;
		(*philo)[i].l_fork = NULL;
		(*philo)[i].r_fork = NULL;
		i++;
	}
	return (0);
}

int	set_table(unsigned int nb_philo, t_fork **fork)
{
	unsigned int	i;

	*fork = malloc(nb_philo * sizeof(t_fork));
	if (!fork)
		return (1);
	i = 0;
	while (i < nb_philo - 1)
	{
		pthread_mutex_init(&((*fork)[i].mutex), NULL);
		(*fork)[i].state = 0;
		i++;
	}
	return (0);
}

int	assign_fork(t_settings set, t_philo *philo, t_fork *forks)
{
	unsigned int i;

	i = 0;
	while (i < set.nb_philo)
	{
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[set.nb_philo - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
	return (0);
}

int	prepare_dinner(t_settings set, t_philo **philo, t_fork **fork)
{
	if (invite_philosophers(set, philo))
		return (1);
	display_philo(*philo, set.nb_philo);
	if (set_table(set.nb_philo, fork))
		return (1);
	if (assign_fork(set, *philo, *fork))
		return (1);
	return (0);
}

int	get_timestamp(struct timeval *tv, struct timezone *tz)
{
	if (gettimeofday(tv, tz) == -1)
		return (1);
	if (!tv || !tz)
		return (1);
	return (0);
}

int fork_available(t_philo *philo)
{
	if (philo->l_fork->state == 0 && philo->r_fork->state == 0)
		return (1);
	return (0);
}

int go_eat(t_philo *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	if (fork_available(philo) == 0)
		return (0);
	philo->state = EAT;
	printf("%lu %d is eating\n", tv.tv_usec, (*philo).id);
	pthread_mutex_lock(&(*philo).l_fork->mutex);
	(*philo).l_fork->state = 1;
	printf("%lu %d has taken a fork\n", tv.tv_usec, (*philo).id);
	(*philo).r_fork->state = 1;
	printf("%lu %d has taken a fork\n", tv.tv_usec, (*philo).id);
	pthread_mutex_unlock(&(*philo).l_fork->mutex);
	usleep(200);
	pthread_mutex_lock(&(*philo).l_fork->mutex);
	(*philo).l_fork->state = 0;
	(*philo).r_fork->state = 0;
	pthread_mutex_unlock(&(*philo).l_fork->mutex);
	printf("%lu %d is thinking\n", tv.tv_usec, (*philo).id);
	philo->state = THINK;
	return (0);
}

int go_sleep(t_philo *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	philo->state = SLEEP; 
	printf("%lu %d is sleeping\n", tv.tv_usec, (*philo).id);
	usleep(200);
	philo->state = THINK;
	return (0);
}

void	*philo_activites(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	go_eat(philo);
	go_sleep(philo);
	return (NULL);
}

int	launch_dinner(t_settings set, t_philo *philo)
{
	pthread_t	*threads;

	threads = malloc(set.nb_philo * sizeof(pthread_t));
	unsigned	int	i;
	unsigned	int j;

	i = 0;
	j = 0;
	while (j < 10)
	{
		while (i < set.nb_philo)
		{
			pthread_create(&threads[i], NULL, philo_activites, &philo[i]);
			i++;
		}
		i = 0;
		while (i < set.nb_philo)
		{
			pthread_join(threads[i], NULL);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_settings	set;
	t_fork		*fork;
	t_philo		*philo;

	if (check_args(argc))
		return (1);
	init_settings(&set, argv, argc);
	//Check the value of each args and chose if it's valid or not like nb_philo musn't be negative or null
	if (prepare_dinner(set, &philo, &fork))
		return (1);
	if (launch_dinner(set, philo))
		return (1);
	free(philo);
	free(fork);
	return (0);
}
