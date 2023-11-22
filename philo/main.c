/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/22 14:40:36 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->started_at = get_time(philo);
	// my_turn(philo);
	// while (!philo->died 
	// 	&& (philo->rules->n_times_must_eat == -1
	// 	|| philo->ate < philo->rules->n_times_must_eat))
	while(1)
	{
		// if (pick_fork(philo))
		// {
		// 	eat(philo);
		// 	place_fork(philo);
		// 	nap(philo);
		// }
		// else
		// 	think(philo);
		ft_usleep(philo->rules->time_to_eat, philo);
		my_turn(philo);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_rules	rules;
	int		i;

	if (argc > 6 || argc < 5)
		exit(1);
	set_rules(argc, argv, &rules);
	if (rules.n_philos > 200)
		exit(1);
	init_mutexes(&rules);
	set_philos(&rules);
	init_philos(&rules);
	detach_threads(&rules);
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&rules.died_mutex);
		if (rules.died)
			break;
		pthread_mutex_unlock(&rules.died_mutex);
		usleep(100);
	}
	i = rules.philo_that_died;
	pthread_mutex_unlock(&rules.died_mutex);
	print_message(&rules.philos_arg[i], DIE_MSG);
	destroy_mutexes(&rules);
	return (0);
}
