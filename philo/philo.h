/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:20:47 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/25 19:11:35 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 1

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stddef.h>

typedef struct s_philo
{
	int	id;
	int	left_fork;
	int	right_fork;
	int	alive;
}	t_philo;

typedef struct s_rules
{
	long			n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_times_must_eat;
	int				forks_state[300];
	pthread_t		philos[300];
	pthread_mutex_t	forks[300];
	pthread_mutex_t	print_mutex;
}	t_rules;

/*utils.c*/
void		init_philosophers(int argc, char *argv[]);
t_rules		*get_rules(void);
long long	get_time(void);

/*string.c*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);

/*converters.c*/
char		*ft_itoa(int n);
int			ft_atoi(const char *nptr);
void		*ft_memcpy(void *dest, const void *src, size_t n);
#endif