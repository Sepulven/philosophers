/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:25 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/19 23:27:02 by asepulve         ###   ########.fr       */
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

	i = 0;
	while (i++ < argc - 1)
	{
		value = ft_atoi(argv[i]);
		buffer = ft_itoa(value);
		if (ft_strncmp(argv[i], buffer, ft_strlen(argv[i])) || value < 0)
		{
			free(buffer);
			error();
		}
		free(buffer);
	}
}

// printf("value %d buffer %s i %d argv %s\n", value, buffer, i,  argv[i]);

void	init_philosophers(int argc, char *argv[])
{
	if (argc > 5 || argc < 4)
		error();
	populate_philosophers(argc, argv);

}

