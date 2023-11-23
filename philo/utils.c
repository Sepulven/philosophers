/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:25 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/23 14:20:16 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long long	get_time(t_philo *philo)
{
	struct timeval		t;
	long long			started_at;

	started_at = philo->rules->started_at;
	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000) - started_at);
}

void	detach_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
		pthread_detach(rules->philos[i++]);
}

int	check_any_died(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	philo->died = 1;
	pthread_mutex_lock(&rules->rules_mutex);
	if (!rules->died)
	{
		rules->died = 1;
		rules->philo_that_died = philo->id;
	}
	pthread_mutex_unlock(&rules->rules_mutex);
	return (0);
}

int	ft_usleep(long long x, t_philo *philo)
{
	long long	started;
	long long	time_to_die;

	time_to_die = philo->rules->time_to_die;
	started = get_time(philo);
	while (get_time(philo) - started < x)
	{
		if (get_time(philo) - philo->turn_timer>= philo->rules->time_to_eat )
		{
			if (philo->turn_counter == philo->rules->n_philos - 1)
				philo->turn_counter = 0;
			else
				philo->turn_counter++;
			philo->turn_timer = get_time(philo);
		}
		if (get_time(philo) - philo->started_at >= time_to_die)
			return (check_any_died(philo));
		usleep(100);
	}
	return (1);
}
