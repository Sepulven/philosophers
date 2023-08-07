/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/07 18:42:20 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_usleep(t_philo *philo, long long x)
{
	long long started;
	
	x = x * 1000;
	started = get_time();
	while (get_time() - started > x)
	{
		(void)philo;
		usleep(100);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	long long i;
	
	philo->started_at = get_time();
	i = 0;
	while (i < philo->rules->time_to_eat * 100)
	{
		if (i == 0)
			print_message(philo, EAT_MSG);
		if (get_time() - philo->started_at >= philo->rules->time_to_die)
		{
			set_died(philo->rules);
			print_message(philo, DIE_MSG);
			destroy_mutexes(philo->rules); 	
			exit(0);
		}
		usleep(1 * 10);
		i++;
	}
	return ;
}

void	nap(t_philo *philo)
{
	long long i;

	i = 0;
	while (i < philo->rules->time_to_sleep * 100)
	{
		if (i == 0)
			print_message(philo, EAT_MSG);
		if (get_time() - philo->started_at >= philo->rules->time_to_die)
		{
			set_died(philo->rules);
			print_message(philo, DIE_MSG);
			destroy_mutexes(philo->rules); 	
			exit(0);
		}
		usleep(1 * 10);
		i++;
	}
	return ;
}

void	think(t_philo *philo)
{
	long long	i;
	long long	started;

	i = 0;
	started = get_time();
	while (!get_turn(philo) && i < philo->rules->time_to_die * 100)
	{
		if (i == 0)
			print_message(philo, "is thinking");
		usleep(1 * 10);
		i++;
	}
	if (get_time() - started >= philo->rules->time_to_die)
	{
		set_died(philo->rules);
		print_message(philo, DIE_MSG);
		destroy_mutexes(philo->rules); 	
		exit(0);
	}
	return ;
}
