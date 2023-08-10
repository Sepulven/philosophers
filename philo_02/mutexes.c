/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:03:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/09 23:17:45 by asepulve         ###   ########.fr       */
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
		pthread_mutex_init(&rules->philos_arg[i].turn_mutex, NULL);
		pthread_mutex_init(&rules->philos_arg[i].died_mutex, NULL);
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
		pthread_mutex_destroy(&rules->philos_arg[i].turn_mutex);
		pthread_mutex_destroy(&rules->philos_arg[i].died_mutex);
		pthread_mutex_destroy(&rules->fork_state_mutex[i]);
		i++;
	}
}

int	get_died(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->died_mutex);
	state = philo->died;
	pthread_mutex_unlock(&philo->died_mutex);
	return (state);
}

int	set_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->died_mutex);
	philo->died = 1;
	pthread_mutex_unlock(&philo->died_mutex);
	return (1);
}
