/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:20:47 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/19 14:24:52 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 1

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t	*tid;
}	t_philo;

#endif