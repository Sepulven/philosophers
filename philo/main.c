/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/22 15:47:20 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->started_at = get_time(philo);
	philo->turn = 0;
	// while (!philo->died 
	// 	&& (philo->rules->n_times_must_eat == -1
	// 	|| philo->ate < philo->rules->n_times_must_eat))
	while(1)
	{
		if (philo->turn)
		{
			pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
			print_message(philo, FORK_MSG);
			pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
			print_message(philo, FORK_MSG);

			eat(philo);

			pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
			
			nap(philo);
		}
		else
			think(philo);
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
