/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/06 20:01:07 by asepulve         ###   ########.fr       */
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
	(void)philo;
	// int	i;

	// i = 0;
	// while ()
	// {
	// 	usleep(1 * 100);
	// 	i++;
	// }
	return ;
}

