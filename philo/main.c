/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/05 15:21:01 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	pick_fork(t_philo *philo)
{
	if	(philo->rules->forks_state[philo->left_fork]
		&& philo->rules->forks_state[philo->right_fork])
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
	if (!pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]))
		philo->rules->forks_state[philo->left_fork] = 0;
	if (!pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]))
		philo->rules->forks_state[philo->left_fork] = 0;
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive)
	{
		usleep(philo->rules->time_to_eat);
		if (pick_fork(philo))
		{
			eat(philo);
			place_fork(philo);
			nap(philo);
		}
		// else
		// 	think(philo);
	}
	return (NULL);
}

void	set_turn(t_rules *rules, int turn)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		if (((turn % 2 == 0) && (i % 2 == 0)) 
			|| ((turn % 2 != 0) && (i % 2 != 0)))
			rules->philos_arg[i].is_turn = 1;
		else
			rules->philos_arg[i].is_turn = 0;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_rules		*rules;
	long		i;
	long		turn_id;
	long		turn_time;

	if (argc > 6 || argc < 5)
	{
		printf("There was an error while parsing.\n");
		exit(1);
	}
	rules = get_rules();
	set_rules(argc, argv, &rules);
	init_philos(rules);
	turn_time = (rules->time_to_die + rules->time_to_eat \
				+ rules->time_to_sleep) * 1000;
	i = 0;
	turn_id = 0;
 	while (!rules->died && (rules->n_times_must_eat == -1 \
	|| turn_id < rules->n_times_must_eat))
	{
		turn_id++;
		set_turn(rules, i++);
		if (i == rules->n_philos)
			i = 0;
		usleep(turn_time);
	}
	return (0);
}
