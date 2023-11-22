/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/22 15:43:55 by asepulve         ###   ########.fr       */
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

int	my_turn(t_philo *philo)
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
	return (philo->turn);
}

void	think(t_philo *philo)
{
	if (philo->died)
		return ;
	if (!my_turn(philo))
		print_message(philo, THINK_MSG);
	while (!philo->turn)
	{
		my_turn(philo);
		ft_usleep(1, philo);
	}
}
