/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:20:47 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/24 11:50:29 by asepulve         ###   ########.fr       */
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
# include <signal.h>

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define NAP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"

typedef struct s_rules	t_rules;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int			id;
	int			turn;
	int			died;
	int			turn_counter;
	int			turn_timer;
	long long	ate;
	long long	started_at;
	long long	started_turn;
	t_rules		*rules;
}	t_philo;

typedef struct s_rules
{
	long long		n_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		n_times_must_eat;
	long long		started_at;
	int				died;
	int				philo_that_died;
	int				n_philos_ate;
	t_philo			philos_arg[300];
	pid_t			philos[300];
}	t_rules;

/*utils.c*/
int				check_any_died(t_philo *philo);
long long		get_time(t_philo *philo);
int				ft_usleep(long long x, t_philo *philo);

/*actions.c*/
void			eat(t_philo *philo);
void			nap(t_philo *philo);
void			think(t_philo *philo);
int				my_turn(t_philo *philo);

/*loggers.c*/
void			log_philos(t_rules *rules);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *str);
int				print_message(t_philo *philo, const char *message);

/*converters.c*/
void			*ft_memcpy(void *dest, const void *src, size_t n);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);

#endif