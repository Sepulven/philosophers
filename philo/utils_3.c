/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:06:22 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/27 17:56:14 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

/*
	* I need to protect the pthread_join this is just a test.
*/
void	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
		pthread_join(rules->philos[i++], NULL);
}
