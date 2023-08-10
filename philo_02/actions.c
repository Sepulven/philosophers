/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/10 00:49:49 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	eat(t_philo *philo)
{
	if (get_died(philo))
		return ;
	philo->started_at = get_time(philo);
	print_message(philo, EAT_MSG);
	ft_usleep(philo->rules->time_to_eat, philo);
	philo->i++;
}

void	nap(t_philo *philo)
{
	if (get_died(philo))
		return ;
	print_message(philo, NAP_MSG);
	ft_usleep(philo->rules->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	long long	i;
	long long	time_to_die;

	i = 0;
	time_to_die = philo->rules->time_to_die;
	if (get_died(philo))
		return ;
	while (!get_turn(philo) && ft_usleep(1, philo))
	{
		if (i == 0)
		{
			print_message(philo, THINK_MSG);
			i = 1;
		}
	}
}

int	pick_fork(t_philo *philo)
{
	if (!get_turn(philo) || get_fork_state(philo, philo->left_fork) \
		|| get_fork_state(philo, philo->right_fork))
		return (0);
	pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
	set_fork_state(philo, philo->left_fork, 1);
	print_message(philo, FORK_MSG);
	pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
	set_fork_state(philo, philo->right_fork, 1);
	print_message(philo, FORK_MSG);
	return (1);
}

int	place_fork(t_philo *philo)
{
	if (!get_fork_state(philo, philo->left_fork)
		&& !get_fork_state(philo, philo->right_fork))
		return (0);
	set_fork_state(philo, philo->left_fork, 0);
	pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
	set_fork_state(philo, philo->right_fork, 0);
	pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
	return (1);
}
