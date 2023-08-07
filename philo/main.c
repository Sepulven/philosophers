/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/06 22:53:12 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	pick_fork(t_philo *philo)
{
	if	(!philo->get_turn(philo) || (philo->rules->forks_state[philo->left_fork]
		|| philo->rules->forks_state[philo->right_fork]))
		return (0);
	if (!pthread_mutex_lock(&philo->rules->forks[philo->left_fork]))
	{
		philo->rules->forks_state[philo->left_fork] = 1;
		print_message(philo, FORK_MSG);
	}
	if (!pthread_mutex_lock(&philo->rules->forks[philo->right_fork]))
	{
		philo->rules->forks_state[philo->left_fork] = 1;
		print_message(philo, FORK_MSG);
	}
	return (1);
}

int	place_fork(t_philo *philo)
{
	if	(!philo->rules->forks_state[philo->left_fork]
		&& !philo->rules->forks_state[philo->right_fork])
			return (0);
	philo->rules->forks_state[philo->left_fork] = 0;
	pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
	philo->rules->forks_state[philo->right_fork] = 0;
	pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->rules->get_died(philo->rules))
	{
		if (pick_fork(philo))
		{
			eat(philo);
			place_fork(philo);
			nap(philo);
		}
		else
 	 		think(philo);
	}
	return (NULL);
}

void	set_turns(t_rules *rules, int turn)
{
	int	i;
	t_philo	*this;

	i = 0;
	while (i < rules->n_philos)
	{
		this = &rules->philos_arg[i];
		if (((turn % 2 == 0) && (i % 2 == 0)) 
			|| ((turn % 2 != 0) && (i % 2 != 0)))
			this->set_turn(this, 1);
		else
			this->set_turn(this, 0);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_rules		rules;
	long		i;
	long		turn_id;

	if (argc > 6 || argc < 5)
		exit(1);
	i = 0;
	turn_id = 0;
	set_rules(argc, argv, &rules);
	init_mutexes(&rules);
	set_philos(&rules);
	init_philos(&rules);
 	while (!rules.get_died(&rules) && (rules.n_times_must_eat == -1 \
	|| turn_id < rules.n_times_must_eat))
	{
		turn_id++;
		set_turns(&rules, i++);
		if (i == rules.n_philos)
			i = 0;
		usleep(rules.turn_time);
	}
	join_threads(&rules);
	destroy_mutexes(&rules);
	return (0);
}
