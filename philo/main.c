/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:52:02 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/20 21:45:07 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	populate_rules(int argc, char *argv[])
{
	int		i;
	int		value;
	char	*buffer;
	long	*attr;

	i = 0;
	attr = &(rules()->n_philos);
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

	// We need to specify which philo takes what forks;
	// Create the mutexes for the forks;

static void	init_philos(void)
{
	long	i;

	i = 0;
	while (i < rules()->n_philos)
	{
		printf("%ld\n", i++);
	}
}

int	main(int argc, char *argv[])
{
	if (argc > 5 || argc < 4)
	{
		printf("There was an error while parsing.\n");
		exit(1);
	}
	populate_rules(argc, argv);
	init_philos();
	// init_mutexes();
	// launch_threads();
}
