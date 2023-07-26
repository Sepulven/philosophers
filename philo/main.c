/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/26 18:21:33 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	set_rules(int argc, char *argv[])
{
	int		i;
	int		value;
	char	*buffer;
	long	*attr;

	i = 0;
	attr = &(get_rules()->n_philos);
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

// * I am going to have a function that has a way of checking 
//	which forks are availble
// * Through its state, so it's going to loop.

// * There is a buffer inside printf, we need to ensure that it's protected
void	print_message(t_rules *rules, long long timestamp, \
		int philo, const char *message)
{
	pthread_mutex_lock(&rules->print_mutex);
	printf("%llu %d %s", timestamp, philo, message);
	pthread_mutex_unlock(&rules->print_mutex);
}

// void	lock_fork(t_rules *rules, t_philo *philo)
// {
// 	pthread_mutex_lock(&rules->forks[fork]);
// 	rules->forks_state[0] = 1;
// }

// void	unlock_fork(t_rules *rules, t_philo *philo)
// {

// }

// void	eat(t_rules *rules, t_philo *philo)
// {
// 	print_message(rules, get_time(), philo->id, "is eating");
// 	usleep(rules->time_to_eat);

// }

// // I need to check the unit used in this example
// void	think(t_rules *rules, t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while ((rules->forks[philo->right_fork] && rules->forks[philo->right_fork])
// 			&&	(i < rules->time_to_die))
// 	{
// 		usleep(1);
// 	}
// 	// The philo died
// }

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

// void	*routine(void *arg)
// {
// 	int		*i;
// 	t_rules	*rules;
// 	t_philo	*philo;

// 	rules = get_rules();
// 	philo = (t_philo *)arg;
// 	while (philo->alive)
// 	{
// 		if (take_forks(rules, philo))
// 		{
// 			eat(rules, philo);
// 			sleep(rules, philo);
// 		}
// 		else
// 			think(rules, philo);
// 	}
// 	return (NULL);
// }

// 1 * Check is there is any fork avaible
// 2 * Check death
// 3 * How do I make a philosophers take a fork?
	// Each philosopher has a fork, they are threads and mutex respectivaly.
	// The forks are mutexes used for the exclusion of other threads to that process;
		// The threads are going to be waiting until the mutex is opened;
	// We need to specify which philo takes what forks;
	// Create the mutexes for the forks;
	// Right after we create the threads it's going to start to get executed;
// printf("sizeof forks_state %ld\n sizeof(int) %ld\n", sizeof (rules->forks_state), sizeof(int));

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

static void	init_philos(void)
{
	t_rules	*rules;
	long	i;
	t_philo	philos[300];

	i = 0;
	rules = get_rules();
	memset(rules->forks_state, 0, sizeof (rules->forks_state));
	set_philos(philos, rules->n_philos);
	// init_mutexes(rules);
	while (i < rules->n_philos)
	{
		printf("Philo n: %ld\n\t\t left %d\n\t\t right %d\n", i,\
		philos[i].left_fork, philos[i].right_fork);
		i++;
	}
	// join_threads(rules);
	// destroy_mutexes(rules);
}

int	main(int argc, char *argv[])
{
	if (argc > 5 || argc < 4)
	{
		printf("There was an error while parsing.\n");
		exit(1);
	}
	(void)set_rules;
	(void)argc;
	(void)argv;
	set_rules(argc, argv);
	init_philos();
}
