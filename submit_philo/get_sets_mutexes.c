/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sets_mutexes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:24:06 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/09 23:23:56 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	get_turn(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->turn_mutex);
	state = philo->turn;
	pthread_mutex_unlock(&philo->turn_mutex);
	return (state);
}

int	set_turn(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->turn_mutex);
	philo->turn = value;
	pthread_mutex_unlock(&philo->turn_mutex);
	return (1);
}

int	get_fork_state(t_philo *philo, int fork)
{
	int	state;

	pthread_mutex_lock(&philo->rules->fork_state_mutex[fork]);
	state = philo->rules->forks_state[fork];
	pthread_mutex_unlock(&philo->rules->fork_state_mutex[fork]);
	return (state);
}

int	set_fork_state(t_philo *philo, int fork, int value)
{
	pthread_mutex_lock(&philo->rules->fork_state_mutex[fork]);
	philo->rules->forks_state[fork] = value;
	pthread_mutex_unlock(&philo->rules->fork_state_mutex[fork]);
	return (1);
}
