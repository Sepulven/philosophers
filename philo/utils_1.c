/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:25 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/06 19:56:19 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"


long long	get_time(t_rules *rules)
{
	struct timeval		t;

	gettimeofday(&t, NULL);
	return (((long long)t.tv_usec - rules->started_at) / 1000);
}

void	set_philos(t_rules *rules)
{
	long	i;

	i = 0;
	while (i < rules->n_philos)
	{
		rules->philos_arg[i].id = (int)i;
		rules->philos_arg[i].alive = 1;
		rules->philos_arg[i].turn = 0;
		rules->philos_arg[i].rules = rules;
		rules->philos_arg[i].get_turn = get_turn;
		rules->philos_arg[i].set_turn = set_turn;
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

	i = 0;
	attr = &(rules->n_philos);
	if (argc - 1 == 4)
		rules->n_times_must_eat = -1;
	while (i++ < argc - 1)
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
	}
	rules->turn_time = attr[1] + attr[2] + attr[3];
	rules->set_died = set_died;
	rules->get_died = get_died;
	rules->died = 0;
}

void	init_philos(t_rules *rules)
{
	long			i;

	i = 0;
	while (i < rules->n_philos)
	{
		pthread_create(&rules->philos[i], NULL, routine, &rules->philos_arg[i]);
		i++;
	}
}
