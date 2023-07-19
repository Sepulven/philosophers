/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:25 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/19 23:53:31 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	error(void)
{
	printf("There was an error while trying to parse your philosophers.\n");
	exit(1);
}

/*
struct timeval	tv;
struct timezone	tz;

gettimeofday(&tv, &tz);
printf("Time %ld\n", tv.tv_sec);
*/

t_philo	*philo(void)
{
	static t_philo	philosopher;

	return (&philosopher);
}

static void	populate_philosophers(int argc, char *argv[])
{
	int		i;
	int		value;
	char	*buffer;
	int		*attr;

	i = 0;
	attr = &(philo()->n_philos);
	while (i++ < argc - 1)
	{
		value = ft_atoi(argv[i]);
		buffer = ft_itoa(value);
		if (ft_strncmp(argv[i], buffer, ft_strlen(argv[i])) || value < 0)
		{
			free(buffer);
			error();
		}
		attr[i - 1] = value;
		free(buffer);
	}
}

void	init_philosophers(int argc, char *argv[])
{
	int	i;
	int	*attr;

	i = 0;
	attr = &(philo()->n_philos);
	if (argc > 5 || argc < 4)
		error();
	populate_philosophers(argc, argv);
	while (i++ < 5)
	{
		printf("attr %d index %d\n", attr[i - 1], i);
	}
}

