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

#include "stdio.h"
#include <sys/types.h>

u_int8_t	check_alpha(char *str)
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

u_int8_t	check_all(char **argv, int argc)
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

u_int8_t	check_args(char **argv, int argc)
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
