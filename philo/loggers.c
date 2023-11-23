/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:18:30 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/23 15:17:33 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	log_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		printf("\nPhilo: %d turn: %d\n\t Died: %d \t left: %d right: %d\n", \
		i, \
		rules->philos_arg[i].turn, \
		rules->philos_arg[i].died, \
		rules->philos_arg[i].left_fork, \
		rules->philos_arg[i].right_fork \
		);
		i++;
	}
}

int	print_message(t_philo *philo, const char *message)
{
	printf("%05llu %d %s\n", get_time(philo), philo->id + 1, message);
	return (1);
}
