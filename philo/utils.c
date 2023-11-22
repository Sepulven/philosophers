/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:25 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/22 14:41:35 by asepulve         ###   ########.fr       */
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

void	check_any_died(t_philo *philo)
{
	t_rules	*rules;
	int		i;

	rules = philo->rules;
	i = 0;
	while (i < rules->n_philos)
	{
		pthread_mutex_lock(&philo->rules->died_mutex);
		if (i != philo->id && rules->died)
		{
			rules->philo_that_died = i;
			pthread_mutex_unlock(&philo->rules->died_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->rules->died_mutex);
		i++;
	}
	philo->died = 1;
}

int	ft_usleep(long long x, t_philo *philo)
{
	long long	started;

	started = get_time(philo);
	while (get_time(philo) - started < x)
	{
		if (philo->turn_timer >= philo->rules->time_to_eat )
		{
			if (philo->turn_counter == philo->rules->n_philos - 1)
				philo->turn_counter = 0;
			else
				philo->turn_counter++;
			philo->turn_timer = 0;
		}
		philo->turn_timer++;
		usleep(1000);
	}
	return (1);
}
