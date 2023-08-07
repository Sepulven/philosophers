/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/07 18:36:39 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	pick_fork(t_philo *philo)
{
	if	(!get_turn(philo) || get_fork_state(philo, philo->left_fork)
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
	if	(!get_fork_state(philo, philo->left_fork)
		&& !get_fork_state(philo, philo->right_fork))
		return (0);
	set_fork_state(philo, philo->left_fork, 0);
	pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
	set_fork_state(philo, philo->right_fork, 0);
	pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->started_at = get_time();
	while (!get_died(philo->rules))
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
	pthread_mutex_lock(&rules->turn_mutex);
	while (i < rules->n_philos)
	{
		this = &rules->philos_arg[i];
		if (((turn % 2 == 0) && (i % 2 == 0)) 
			|| ((turn % 2 != 0) && (i % 2 != 0)))
			this->turn = 1;
		else
			this->turn = 0;
		i++;
	}
	pthread_mutex_unlock(&rules->turn_mutex);
}

int	main(int argc, char *argv[])
{
	t_rules		rules;
	long		i;
	long		turn_id;
	
	i = 0;
	turn_id = 0;
	if (argc > 6 || argc < 5)
		exit(1);
	set_rules(argc, argv, &rules);
	init_mutexes(&rules);
	set_philos(&rules);
	init_philos(&rules);
 	while (!get_died(&rules) && (rules.n_times_must_eat == -1 \
	|| turn_id < rules.n_times_must_eat))
	{
		turn_id++;
		set_turns(&rules, i++);
		if (i == rules.n_philos)
			i = 0;
		usleep(rules.turn_time * 1000);
	}
	join_threads(&rules);
	destroy_mutexes(&rules);
	return (0);
}
