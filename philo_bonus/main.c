/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/25 14:39:15 by asepulve         ###   ########.fr       */
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
	sem_unlink(FORKS_SEM);
	sem_unlink(RULES_SEM);
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

void	routine(t_philo	*philo)
{
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
	exit(0);
}

void	init_philos(t_rules *rules)
{
	int				i;
	pid_t			pid;

	rules->started_at = 0;
	rules->started_at = get_time(&rules->philos_arg[0]);
	rules->died = 0;
	rules->n_philos_ate = 0;
	rules->philo_that_died = -1;
	i = 0;
	while (i < rules->n_philos)
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			routine(&rules->philos_arg[i]);
		else
		{
			rules->philos[i] = pid;
			pthread_create(&rules->philos_managers[i], NULL, \
			manager, &rules->philos_arg[i]);
			pthread_detach(rules->philos_managers[i]);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_rules	rules;

	if (argc > 6 || argc < 5)
		exit(1);
	set_rules(argc, argv, &rules);
	if (rules.n_philos > 200)
		exit(1);
	set_philos(&rules);
	rules.forks_sem = sem_open(FORKS_SEM, O_CREAT | O_EXCL, 0644, \
	rules.n_philos);
	rules.rules_sem = sem_open(RULES_SEM, O_CREAT | O_EXCL, 0644, 1);
	init_philos(&rules);
	while (!usleep(100))
	{
		sem_wait(rules.rules_sem);
		if (rules.died || rules.n_philos_ate == rules.n_philos)
			break ;
		sem_post(rules.rules_sem);
	}
	sem_close(rules.rules_sem);
	sem_close(rules.rules_sem);
	sem_unlink(RULES_SEM);
	sem_unlink(FORKS_SEM);
	return (0);
}
