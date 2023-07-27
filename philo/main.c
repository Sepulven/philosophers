/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/27 19:43:53 by asepulve         ###   ########.fr       */
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

void	*routine(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	(void)i;
	(void)philo;
	// while (philo->alive)
	// {
	// 	if (pick_fork(rules, philo))
	// 	{
	// 		eat(rules, philo);
	// 		sleep(rules, philo);
	// 	}
	// 	else
	// 		think(rules, philo);
	// }
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
		pthread_create(&rules->philos[i], NULL, routine, &rules->philos_arg[i]);
		i++;
	}
	join_threads(rules);
	destroy_mutexes(rules);
}

// printf("sizeof forks_state %ld\n sizeof(int) %ld\n", sizeof
// (rules->forks_state), sizeof(int));

int	main(int argc, char *argv[])
{
	t_rules		*rules;
	long		i;
	long		turn_time;

	i = 0;
	rules = get_rules();
	if (argc > 5 || argc < 4)
	{
		printf("There was an error while parsing.\n");
		exit(1);
	}
	set_rules(argc, argv);
	init_philos();
	turn_time = (rules->time_to_die + rules->time_to_eat \
				+ rules->time_to_sleep) * 1000;
	// usleep(30000);
	printf("turn_time: %ld\n", turn_time);
	while (!rules->died && !(rules->n_times_must_eat > 0 \
	&& i < rules->n_times_must_eat))
	{
		printf("%ld \n", i++);
		usleep(turn_time);
	}
	printf("\n");
}
