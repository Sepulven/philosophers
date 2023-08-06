/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:03:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/06 14:20:33 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	init_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	memset(rules->forks_state, 0, sizeof (rules->forks_state));
	while (i < 300)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
		{
			printf("We couldn't initialize the mutex.\n");
			exit(0);
		}
		i++;
	}
	pthread_mutex_init(&rules->turn_mutex, NULL);
	pthread_mutex_init(&rules->died_mutex, NULL);
	pthread_mutex_init(&rules->print_mutex, NULL);
}

void	destroy_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		if (pthread_mutex_destroy(&rules->forks[i]))
			exit(0);
		i++;
	}
	pthread_mutex_destroy(&rules->turn_mutex);
	pthread_mutex_destroy(&rules->died_mutex);
	pthread_mutex_destroy(&rules->print_mutex);
}

int	get_died(t_rules *rules)
{
	int	state;

	pthread_mutex_lock(&rules->died_mutex);
	state = rules->died;
	pthread_mutex_unlock(&rules->died_mutex);
	return (state);
}
int	set_died(t_rules *rules)
{
	pthread_mutex_lock(&rules->died_mutex);
	rules->died = 1;
	pthread_mutex_unlock(&rules->died_mutex);
	return (1);
}


