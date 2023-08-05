/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:28:21 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/05 23:34:03 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int get_turn(t_philo* philo)
{
    int state;

    pthread_mutex_lock(&philo->rules->turn_mutex);
    state = philo->turn;
    pthread_mutex_unlock(&philo->rules->turn_mutex);
    return (state);
}

int set_turn(t_philo* philo, int value)
{
    pthread_mutex_lock(&philo->rules->turn_mutex);
    philo->turn = value;
    pthread_mutex_unlock(&philo->rules->turn_mutex);
    return (1);
}