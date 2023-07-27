/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:20:47 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/27 17:57:29 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 1

# include <stdio.h>
# include <string.h>
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
	t_philo			philos_arg[300];
	pthread_t		philos[300];
	pthread_mutex_t	forks[300];
	pthread_mutex_t	print_mutex;
}	t_rules;



/*utils_1.c*/
long long	get_time(void);
t_rules		*get_rules(void);
void		set_philos(t_philo philos[300], long n_philos);
void		init_philos(void);

/*utils_2.c*/
void		init_mutexes(t_rules *rules);
void		destroy_mutexes(t_rules *rules);
void		print_message(t_rules *rules, long long timestamp, \
			int philo, const char *message);

/*utils_3.c*/
void		join_threads(t_rules *rules);

/*actions.c*/
void		eat(t_rules *rules, t_philo *philo);
void		nap(t_rules *rules, t_philo *philo);
void		think(t_rules *rules, t_philo *philo);
void		pick_fork(t_rules *rules, t_philo *philo);
void		place_fork(t_rules *rules, t_philo *philo);


/*string.c*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);

/*converters.c*/
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
#endif