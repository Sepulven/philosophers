/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:18:30 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/03 20:39:36 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	log_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		printf("\nPhilo: %d turn: %d\n\t Alive: %d \t left: %d right: %d\n", \
		i, \
		rules->philos_arg[i].is_turn,\
		rules->philos_arg[i].alive, \
		rules->philos_arg[i].left_fork, \
		rules->philos_arg[i].right_fork \
		);
		i++;
	}
}
