/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:03:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/07 22:32:11 by asepulve         ###   ########.fr       */
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
	pthread_mutex_init(&rules->fork_state_mutex, NULL);
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
	pthread_mutex_destroy(&rules->fork_state_mutex);
}

int	get_died(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->rules->died_mutex);
	state = philo->rules->died;
	pthread_mutex_unlock(&philo->rules->died_mutex);
	return (state);
}
int	set_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->died_mutex);
	// print_message(philo, DIE_MSG);
	philo->rules->died = 1;
	pthread_mutex_unlock(&philo->rules->died_mutex);
	return (1);
}


