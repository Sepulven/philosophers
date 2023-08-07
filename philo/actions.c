/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/07 16:07:37 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	eat(t_philo *philo)
{
	print_message(philo, EAT_MSG);
	usleep(philo->rules->time_to_eat *  1000);
	return ;
}

void	nap(t_philo *philo)
{
	print_message(philo, NAP_MSG);
	usleep(philo->rules->time_to_sleep * 1000);
	return ;
}

void	think(t_philo *philo)
{
	long long	i;

	i = 0;
	while (!get_turn(philo) && i < philo->rules->time_to_die)
	{
		if (i == 0)
			print_message(philo, "is thinking");
		usleep(1 * 1000); // Must wait 1 milisecond
		i++;
	}
	if (i >= philo->rules->time_to_die)
		set_died(philo->rules);
	return ;
}

