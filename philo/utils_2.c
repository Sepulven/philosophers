/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:03:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/27 17:42:38 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	init_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < 300)
	{
		if (!pthread_mutex_init(&rules->forks[i], NULL))
		{
			printf("We couldn't initialize the mutex.\n");
			exit(0);
		}
		i++;
	}
}

void	destroy_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < 300)
	{
		if (!pthread_mutex_destroy(&rules->forks[i]))
		{
			printf("We couldn't destroy the mutex.\n");
			exit(0);
		}
		i++;
	}
}

void	print_message(t_rules *rules, long long timestamp, \
		int philo, const char *message)
{
	pthread_mutex_lock(&rules->print_mutex);
	printf("%llu %d %s", timestamp, philo, message);
	pthread_mutex_unlock(&rules->print_mutex);
}
