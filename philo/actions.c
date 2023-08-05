/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/05 01:53:06 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	eat(t_rules *rules, t_philo *philo)
{
	(void)rules;
	(void)philo;
	// print_message(rules, get_time(), philo->id, "is eating");
	// usleep(rules->time_to_eat);
	return ;
}

void	nap(t_rules *rules, t_philo *philo)
{
	(void)rules;
	(void)philo;
	return ;
}

void	think(t_rules *rules, t_philo *philo)
{
	(void)rules;
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

void	place_fork(t_rules *rules, t_philo *philo)
{
	(void)rules;
	(void)philo;
	// pthread_mutex_lock(&rules->forks[fork]);
	// rules->forks_state[0] = 1;

	return ;
}
