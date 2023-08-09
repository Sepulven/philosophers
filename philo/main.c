/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/09 13:53:52 by asepulve         ###   ########.fr       */
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
	while (!philo->died)
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

int	even_turn(int turn_id, int philo_id)
{
	return (turn_id % 2 == 0 && philo_id % 2 == 0);
}

int	odd_turn(int turn_id, int philo_id)
{
	return (turn_id % 2 != 0 && philo_id % 2 != 0);
}

void	set_turns(t_rules *rules, int turn)
{
	int		i;
	int		result;

	i = 0;
	while (i < rules->n_philos)
	{
		if ((rules->n_philos % 2 == 0 && turn % 2 == 0)
			|| (rules->n_philos % 2 != 0 && i < turn && turn % 2 == 0))
			result = even_turn(turn, i);
		else if ((rules->n_philos % 2 == 0 && turn % 2 != 0)
			|| (rules->n_philos % 2 != 0 && i < turn && turn % 2 != 0))
			result = odd_turn(turn, i);
		else if (rules->n_philos % 2 != 0 && i == turn)
			result = 0;
		else if (rules->n_philos % 2 != 0 && i > turn && turn % 2 == 0)
			result = odd_turn(turn + 1, i);
		else if (rules->n_philos % 2 != 0 && i > turn && turn % 2 != 0)
			result = even_turn(turn + 1, i);
		set_turn(&rules->philos_arg[i], result);
		i++;
	}
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
	set_turns(&rules, 0);
	init_philos(&rules);
 	while (!rules.died && (rules.n_times_must_eat == -1 \
	|| turn_id < rules.n_times_must_eat))
	{
		usleep(rules.time_to_eat * 1000);
		turn_id++;
		set_turns(&rules, i++);
		if (i == rules.n_philos)
			i = 0;
	}
	join_threads(&rules);
	destroy_mutexes(&rules);
	return (0);
}
