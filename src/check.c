/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:36:03 by dernst            #+#    #+#             */
/*   Updated: 2025/07/16 15:36:21 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

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
