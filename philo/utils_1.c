/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:25 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/05 23:45:33 by asepulve         ###   ########.fr       */
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

void	set_philos(t_rules *rules)
{
	long	i;

	i = 0;
	while (i < rules->n_philos)
	{
		rules->philos_arg[i].id = (int)i;
		rules->philos_arg[i].alive = 1;
		rules->philos_arg[i].left_fork = i;
		rules->philos_arg[i].rules = rules;
		rules->philos_arg[i].get_turn = get_turn;
		rules->philos_arg[i].set_turn = set_turn;
		if (i + 1 == rules->n_philos)
			rules->philos_arg[i].right_fork = 0;
		else
			rules->philos_arg[i].right_fork = i + 1;
		i++;
	}
}

void	set_rules(int argc, char *argv[], t_rules *rules)
{
	int		i;
	int		value;
	char	*buffer;
	long	*attr;

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
	rules->set_died = set_died;
	rules->get_died = get_died;
	rules->died = 0;
}

void	init_philos(t_rules *rules)
{
	long	i;

	i = 0;
	while (i < rules->n_philos)
	{
		pthread_create(&rules->philos[i], NULL, routine, &rules->philos_arg[i]);
		i++;
	}
}
