/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:18:30 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/24 11:34:51 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	log_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		printf("\nPhilo: %d turn: %d\n\t Died: %d\n", \
		i, \
		rules->philos_arg[i].turn, \
		rules->philos_arg[i].died \
		);
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	print_message(t_philo *philo, const char *message)
{
	printf("%05llu %d %s\n", get_time(philo), philo->id + 1, message);
	return (1);
}
