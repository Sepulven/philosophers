/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:18:30 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/05 15:18:42 by asepulve         ###   ########.fr       */
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

void	print_message(t_philo *philo,  const char *message)
{
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%llu %d %s\n", get_time(), philo->id, message);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	return ;
}
