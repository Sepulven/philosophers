/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:33:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/20 21:21:33 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*eating(void *arg)
{
	return (NULL);
}

void	*sleeping(void *arg)
{
	return (NULL);
}

void	*thinking(void *arg)
{
	return (NULL);
}

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive)
	{
		// If philo turn 
			// Philo eat
			// Philo sleep 
		// else
			// Philo think
	}
	return (NULL);
}

void	*check_deads(t_philo philo)
{

	return (NULL);
}
