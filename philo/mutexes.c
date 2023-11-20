/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:03:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/20 14:05:36 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	init_mutexes(t_rules *rules)
{
	int	i;

	memset(rules->forks_state, 0, sizeof (rules->forks_state));
	i = 0;
	while (i < rules->n_philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		pthread_mutex_init(&rules->fork_state_mutex[i], NULL);
		i++;
	}
}

void	destroy_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->fork_state_mutex[i]);
		i++;
	}
}
