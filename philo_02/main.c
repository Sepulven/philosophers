/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/10 01:15:28 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->started_at = get_time(philo);
	while (!get_died(philo) \
		&& (philo->rules->n_times_must_eat == -1 \
		|| philo->i < philo->rules->n_times_must_eat))
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

void	*manager(void *arg)
{
	t_rules			*rules;
	long			i;

	i = 1;
	rules = (t_rules *)arg;
	while (1)
	{
		usleep(rules->time_to_eat * 1000);
		set_turns(rules, i++);
		if (i == rules->n_philos)
			i = 0;
	}
}

int	main(int argc, char *argv[])
{
	t_rules			rules;
	pthread_t		manager_thread;
	int				i;

	if (argc > 6 || argc < 5)
		exit(1);
	set_rules(argc, argv, &rules);
	if (rules.n_philos > 200)
		exit(1);
	init_mutexes(&rules);
	set_philos(&rules);
	init_philos(&rules);
	pthread_create(&manager_thread, NULL, manager, &rules);
	pthread_detach(manager_thread);
	detach_threads(&rules);
	i = 0;
	while (!get_died(&rules.philos_arg[i]))
	{
		if (i == rules.n_philos)
			i = 0;
		i++;
	}
	print_message(&rules.philos_arg[i], DIE_MSG);
	destroy_mutexes(&rules);
	return (0);
}
