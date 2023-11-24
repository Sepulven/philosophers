/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:34:29 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/24 15:34:42 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	kill_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
		kill(rules->philos[i++], SIGTERM);
}
