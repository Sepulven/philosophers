/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:20:47 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/05 15:20:42 by asepulve         ###   ########.fr       */
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

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define NAP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "dies"

typedef struct s_rules t_rules;

#define DEBUG write(1, "ok\n", 3);

typedef struct s_philo
{
	int		id;
	int		left_fork;
	int		right_fork;
	int		alive;
	int		is_turn;
	t_rules	*rules;
}	t_philo;

typedef struct s_rules
{
	long			n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_times_must_eat;
	int				died;
	int				forks_state[300];
	t_philo			philos_arg[300];
	pthread_t		philos[300];
	pthread_mutex_t	forks[300];
	pthread_mutex_t	print_mutex;
}	t_rules;

/*utils_1.c*/
long long	get_time(void);
t_rules		*get_rules(void);
void		set_philos(t_rules *rules);
void		init_philos(t_rules *rules);
void		set_rules(int argc, char *argv[], t_rules **rules)


/*utils_2.c*/
void		init_mutexes(t_rules *rules);
void		destroy_mutexes(t_rules *rules);

/*utils_3.c*/
void		join_threads(t_rules *rules);

/*actions.c*/
void		eat(t_philo *philo);
void		nap(t_philo *philo);
void		think(t_philo *philo);
int			pick_fork(t_philo *philo);
int			place_fork(t_philo *philo);

/*string.c*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);

/*loggers.c*/
void		log_philos(t_rules *rules);
void		print_message(t_philo *philo, const char *message);

/*converters.c*/
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
#endif