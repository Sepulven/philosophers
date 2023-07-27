/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/27 17:52:46 by asepulve         ###   ########.fr       */
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


void	*routine(void *arg)
{
	(void)arg;
	// int		*i;
	// t_rules	*rules;
	// t_philo	*philo;

	// rules = get_rules();
	// philo = (t_philo *)arg;
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

// printf("sizeof forks_state %ld\n sizeof(int) %ld\n", sizeof (rules->forks_state), sizeof(int));

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
	/*
	loop right here to chekc whether the philo has died or not
	if not go to next turn.
	*/
}
