/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:25 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/27 17:41:16 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"


long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 100) + (t.tv_usec / 1000));
}

t_rules	*get_rules(void)
{
	static t_rules	rules;

	return (&rules);
}

void	set_philos(t_philo philos[300], long n_philos)
{
	long	i;

	i = 0;
	while (i < n_philos)
	{
		philos[i].id = (int)i;
		philos[i].alive = 1;
		philos[i].left_fork = i;
		if (i + 1 == n_philos)
			philos[i].right_fork = 0;
		else
			philos[i].right_fork = i + 1;
		i++;
	}
}

void	init_philos(void)
{
	t_rules	*rules;
	long	i;

	i = 0;
	rules = get_rules();
	memset(rules->forks_state, 0, sizeof (rules->forks_state));
	set_philos(rules->philos_arg, rules->n_philos);
	init_mutexes(rules);
	while (i < rules->n_philos)
	{
		printf("Philo n: %ld\n\t\t left %d\n\t\t right %d\n", i,\
		rules->philos_arg[i].left_fork, rules->philos_arg[i].right_fork);
		i++;
	}
	join_threads(rules);
	destroy_mutexes(rules);
}


