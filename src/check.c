/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:36:03 by dernst            #+#    #+#             */
/*   Updated: 2025/08/07 14:57:31 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"
#include <sys/types.h>

unsigned int	check_alpha(char *str)
{
	while (*str && str)
	{
		if (*str < 48 || *str > 57)
		{
			return (1);
		}
		str++;
	}
	return (0);
}

unsigned int	check_all(char **argv, int argc)
{
	u_int8_t	i;

	i = 1;
	while (i < argc)
	{
		if (check_alpha(argv[i]))
		{
			printf("Invalid Format !\n");
			return (1);
		}
		i++;
	}
	return (0);
}

unsigned int	check_args(char **argv, int argc)
{
	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			printf("Not enough args\n");
		if (argc > 6)
			printf("Too many args\n");
		return (1);
	}
	if (check_all(argv, argc))
		return (1);
	return (0);
}

bool	fork_available(t_philo *philo, unsigned long time_start)
{
	if (choose_forks(philo, time_start))
		return (DEAD);
	return (0);
}
