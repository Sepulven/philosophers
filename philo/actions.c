/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/08 13:06:51 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// x = miliseconds
int	ft_usleep(long long x, t_philo *philo)
{
	long long started;
	long long time_to_die;

	time_to_die = philo->rules->time_to_die;
	started = get_time();
	while (get_time() - started < x && !philo->rules->died)
	{
		if (get_time() - philo->started_at >= time_to_die)
		{
			philo->rules->died = 1;
			break ;
		}
		usleep(100);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	philo->started_at = get_time();
	print_message(philo, EAT_MSG);
	ft_usleep(philo->rules->time_to_eat, philo);
}

void	nap(t_philo *philo)
{
	print_message(philo, NAP_MSG);
	ft_usleep(philo->rules->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	long long i;
	long long time_to_die;

	i = 0;
	time_to_die = philo->rules->time_to_die;
	while (!get_turn(philo))
	{
		if (i == 0)
			print_message(philo, THINK_MSG);
		if (get_time() - philo->started_at >= time_to_die)
		{
			philo->rules->died = 1;
			break;
		}
		ft_usleep(1, philo);
		i++;
	}
}
