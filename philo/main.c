/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/24 23:06:43 by asepulve         ###   ########.fr       */
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
		rules->philos_arg[i].turn_counter = 0;
		rules->philos_arg[i].turn_timer = 0;
		rules->philos_arg[i].rules = rules;
		rules->philos_arg[i].ate = 0;
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
	rules->died = 0;
	rules->n_philos_ate = 0;
	rules->philo_that_died = -1;
	i = 0;
	while (i < rules->n_philos)
	{
		pthread_create(&rules->philos[i], NULL, routine, &rules->philos_arg[i]);
		pthread_detach(rules->philos[i]);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->started_at = get_time(philo);
	philo->turn_timer = get_time(philo);
	while (!philo->died
		&& (philo->rules->n_times_must_eat == -1
			|| philo->ate < philo->rules->n_times_must_eat))
	{
		if (my_turn(philo))
		{
			eat(philo);
			nap(philo);
		}
		else
			think(philo);
	}
	pthread_mutex_lock(&philo->rules->rules_mutex);
	philo->rules->n_philos_ate++;
	if (philo->rules->n_philos_ate != philo->rules->n_philos)
		think(philo);
	pthread_mutex_unlock(&philo->rules->rules_mutex);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_rules	rules;

	if (argc > 6 || argc < 5)
		exit(1);
	set_rules(argc, argv, &rules);
	if (rules.n_philos > 200)
		exit(1);
	mutexes(&rules, 'i');
	set_philos(&rules);
	init_philos(&rules);
	while (!usleep(100))
	{
		pthread_mutex_lock(&rules.rules_mutex);
		if (rules.died || rules.n_philos_ate == rules.n_philos)
			break ;
		pthread_mutex_unlock(&rules.rules_mutex);
	}
	if (rules.philo_that_died != -1)
		print_message(&rules.philos_arg[rules.philo_that_died], DIE_MSG);
	pthread_mutex_unlock(&rules.rules_mutex);
	mutexes(&rules, 'd');
	return (0);
}
