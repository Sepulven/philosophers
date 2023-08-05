/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/05 02:01:23 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"


static void	set_rules(int argc, char *argv[])
{
	int		i;
	int		value;
	char	*buffer;
	long	*attr;
	t_rules	*rules;

	i = 0;
	rules = get_rules();
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
}
/*
(rules->forks_state[philo->left_fork] == 0
			&& rules->forks_state[philo->right_fork] == 0
*/

int	pick_fork(t_rules *rules, t_philo *philo)
{

	if	(rules->forks_state[philo->left_fork] == 0
			&& rules->forks_state[philo->right_fork] == 0)
		return (0);
	if (!pthread_mutex_lock(&rules->forks[philo->left_fork]))
	{
		rules->forks_state[philo->left_fork] = 1;
		print_message(rules, get_time(), philo->id, "has taken a fork");
	}
	if (!pthread_mutex_lock(&rules->forks[philo->right_fork]))
	{
		rules->forks_state[philo->right_fork] = 1;
		print_message(rules, get_time(), philo->id, "has taken a fork");
	}
	return (1);
}

void	*routine(void *arg)
{
	int		i;
	t_rules	*rules;
	t_philo	*philo;

	i = *(int *)arg;
	rules = get_rules();
	philo = &rules->philos_arg[i];
	DEBUG
	while (philo->alive)
	{
		DEBUG
		if (pick_fork(rules, philo))
		{

			eat(rules, philo);
			nap(rules, philo);
		}
		else
			think(rules, philo);
	}
	return (NULL);
}

void	init_philos(void)
{
	t_rules	*rules;
	long	i;

	i = 0;
	rules = get_rules();
	memset(rules->forks_state, 0, sizeof (rules->forks_state));
	init_mutexes(rules);
	set_philos(rules->philos_arg, rules->n_philos);
	while (i < rules->n_philos)
	{
		pthread_create(&rules->philos[i], NULL, routine, &i);
		i++;
	}
	join_threads(rules);
	destroy_mutexes(rules);
}

// printf("sizeof forks_state %ld\n sizeof(int) %ld\n", sizeof
// (rules->forks_state), sizeof(int));

void	set_turn(t_rules *rules, int turn)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		if (((turn % 2 == 0) && (i % 2 == 0)) 
			|| ((turn % 2 != 0) && (i % 2 != 0)))
			rules->philos_arg[i].is_turn = 1;
		else
			rules->philos_arg[i].is_turn = 0;
		i++;
	}
}

int		main(int argc, char *argv[])
{
	t_rules		*rules;
	long		i;
	long		turn_id;
	long		turn_time;

	if (argc > 6 || argc < 5)
	{
		printf("There was an error while parsing.\n");
		exit(1);
	}
	rules = get_rules();
	set_rules(argc, argv);
	init_philos();
	turn_time = (rules->time_to_die + rules->time_to_eat \
				+ rules->time_to_sleep) * 1000;
	i = 0;
	turn_id = 0;
 	while (!rules->died && (rules->n_times_must_eat == -1 \
	|| turn_id < rules->n_times_must_eat))
	{
		turn_id++;
		set_turn(rules, i++);
		if (i == rules->n_philos)
			i = 0;
		usleep(turn_time);
	}
}
