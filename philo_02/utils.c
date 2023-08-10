/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:25 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/10 01:12:05 by asepulve         ###   ########.fr       */
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
		if (i != philo->id && get_died(&rules->philos_arg[i]))
			return ;
		i++;
	}
	set_died(philo);
}

int	ft_usleep(long long x, t_philo *philo)
{
	long long	started;
	long long	time_to_die;

	time_to_die = philo->rules->time_to_die;
	started = get_time(philo);
	while (get_time(philo) - started < x)
	{
		if (get_time(philo) - philo->started_at >= time_to_die)
		{
			check_any_died(philo);
			return (0);
		}
		usleep(100);
	}
	return (1);
}
