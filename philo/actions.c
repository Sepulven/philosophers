/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/22 14:49:10 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	eat(t_philo *philo)
{
	if (philo->died)
		return ;
	philo->started_at = get_time(philo);
	print_message(philo, EAT_MSG);
	ft_usleep(philo->rules->time_to_eat, philo);
	philo->turn = 0;
	philo->ate++;
}

void	nap(t_philo *philo)
{
	if (philo->died)
		return ;
	print_message(philo, NAP_MSG);
	ft_usleep(philo->rules->time_to_sleep, philo);
}
/*
NOTE: If it is a even turn then the even philosophers must eat
*/
int	even(t_philo *philo, int turn)
{
	return ((turn % 2 == 0 && philo->id % 2 == 0) 
		|| (turn % 2 != 0 && philo->id % 2 != 0));
}

void	my_turn(t_philo *philo)
{
	t_rules 		*rules;
	int				n_philos;
	int				turn;

	turn = philo->turn_counter;
	rules = philo->rules;
	n_philos = rules->n_philos;
	if (n_philos % 2 == 0)
		philo->turn = even(philo, turn);
	if (n_philos % 2 != 0)
	{
		if (philo->id < turn)
			philo->turn = even(philo, turn);
		if (philo->id > turn)
			philo->turn = even(philo, turn + 1);
		if (philo->id == turn)
			philo->turn = 0;
	}
	// printf("%d\n", philo->turn_counter);
	printf("[%d]%d : %d\n", philo->id, philo->turn, philo->turn_counter);
}

void	think(t_philo *philo)
{
	long long	i;

	i = 0;
	if (philo->died)
		return ;
	while (!philo->turn && ft_usleep(1, philo))
	{
		if (i == 0)
		{
			print_message(philo, THINK_MSG);
			i = 1;
		}
		my_turn(philo);
	}
}

int	pick_fork(t_philo *philo)
{
	if (!philo->turn || get_fork_state(philo, philo->left_fork) \
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
