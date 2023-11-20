/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:34:27 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/20 16:57:46 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	set_philos(t_rules *rules)
{
	long	i;

	i = 0;
	while (i < rules->n_philos)
	{
		rules->philos_arg[i].id = (int)i;
		rules->philos_arg[i].died = 0;
		rules->philos_arg[i].turn = 0;
		rules->philos_arg[i].rules = rules;
		rules->philos_arg[i].ate = 0;
		rules->philos_arg[i].turn_counter = 0;
		rules->philos_arg[i].turn_timer = 0;
		rules->philos_arg[i].left_fork = (int)i;
		if (i + 1 == rules->n_philos)
			rules->philos_arg[i].right_fork = 0;
		else
			rules->philos_arg[i].right_fork = (int)i + 1;
		i++;
	}
}

void	set_rules(int argc, char *argv[], t_rules *rules)
{
	int			i;
	int			value;
	char		*buffer;
	long long	*attr;

	attr = &(rules->n_philos);
	if (argc - 1 == 4)
		rules->n_times_must_eat = -1;
	i = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		buffer = ft_itoa(value);
		if (ft_strncmp(argv[i], buffer, ft_strlen(argv[i])) || value < 0)
		{
			free(buffer);
			printf("There was an error while parsing.\n");
			exit(1);
		}
		attr[i - 1] = value;
		free(buffer);
		i++;
	}
}

void	init_philos(t_rules *rules)
{
	struct timeval	t;
	int				i;

	gettimeofday(&t, NULL);
	rules->started_at = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	i = 0;
	while (i < rules->n_philos)
	{
		pthread_create(&rules->philos[i], NULL, routine, &rules->philos_arg[i]);
		i++;
	}
}
