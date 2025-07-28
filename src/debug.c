/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:15:31 by dernst            #+#    #+#             */
/*   Updated: 2025/07/16 15:17:34 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"

void	display_data(t_data data)
{
	printf("nb_philo   : %d\n", data.nb_philo);
	printf("time_die   : %d\n", data.time_die);
	printf("time_eat   : %d\n", data.time_eat);
	printf("time_sleep : %d\n", data.time_sleep);
	printf("nb_eat     : %d\n", data.nb_eat);
	printf("state      : %d\n", data.state);
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
