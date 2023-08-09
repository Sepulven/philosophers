/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/09 15:32:40 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->started_at = get_time(philo);
	while (!philo->died && !philo->rules->died)
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

int	main(int argc, char *argv[])
{
	t_rules		rules;
	struct timeval		t;

	if (argc > 6 || argc < 5)
		exit(1);
	set_rules(argc, argv, &rules);
	init_mutexes(&rules);
	set_philos(&rules);
	set_turns(&rules, 0);
	gettimeofday(&t, NULL);
	rules.started_at = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	init_philos(&rules);
	join_threads(&rules);
	destroy_mutexes(&rules);
	return (0);
}
