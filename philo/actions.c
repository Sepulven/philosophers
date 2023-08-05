/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/05 15:07:51 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	eat(t_philo *philo)
{

	print_message(philo, EAT_MSG);
	usleep(philo->rules->time_to_eat);
	return ;
}

void	nap(t_philo *philo)
{
	print_message(philo, NAP_MSG);
	usleep(philo->rules->time_to_sleep);
	return ;
}

void	think(t_philo *philo)
{
	(void)philo;
	// int	i;

	// i = 0;
	// while ((rules->forks[philo->right_fork] && rules->forks[philo->right_fork])
	// 	&&	(i < rules->time_to_die))
	// {
	// 	usleep(1);
	// 	i++;
	// }
	return ;
}

