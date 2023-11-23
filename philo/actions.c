/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/23 12:54:43 by asepulve         ###   ########.fr       */
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
int	my_turn(t_philo *philo)
{
	t_rules 		*rules;
	int				n_philos;
	int				turn;

	turn = philo->turn_counter;
	rules = philo->rules;
	n_philos = rules->n_philos;
	if (n_philos % 2 == 0)
		philo->turn = ((turn % 2 == 0 && philo->id % 2 == 0) 
		|| (turn % 2 != 0 && philo->id % 2 != 0));
	if (n_philos % 2 != 0)
	{
		if (philo->id < turn)
			philo->turn = ((turn % 2 == 0 && philo->id % 2 == 0) 
		|| (turn % 2 != 0 && philo->id % 2 != 0));
		if (philo->id > turn)
			philo->turn = (((turn + 1) % 2 == 0 && philo->id % 2 == 0) 
		|| ((turn + 1) % 2 != 0 && philo->id % 2 != 0));
		if (philo->id == turn)
			philo->turn = 0;
	}
	return (philo->turn);
}


// I am going to try to add the timer through a real timer
void	think(t_philo *philo)
{
	long long	time_to_die;

	if (philo->died)
		return ;
	if (!my_turn(philo))
		print_message(philo, THINK_MSG);
	time_to_die = philo->rules->time_to_die;
	while (!my_turn(philo))
	{
		if (get_time(philo) - philo->turn_timer>= philo->rules->time_to_eat )
		{
			if (philo->turn_counter == philo->rules->n_philos - 1)
				philo->turn_counter = 0;
			else
				philo->turn_counter++;
			philo->turn_timer = get_time(philo);
		}
		if (get_time(philo) - philo->started_at >= time_to_die)
			return ((void)check_any_died(philo));
		usleep(100);
	}
}
