/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sets_mutexes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:24:06 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/20 13:10:31 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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
