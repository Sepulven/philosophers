/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turns.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:16:32 by asepulve          #+#    #+#             */
/*   Updated: 2023/08/09 15:59:02 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	even_turn(int turn_id, int philo_id)
{
	return (turn_id % 2 == 0 && philo_id % 2 == 0);
}

static int	odd_turn(int turn_id, int philo_id)
{
	return (turn_id % 2 != 0 && philo_id % 2 != 0);
}

void	set_turns(t_rules *rules, int turn)
{
	int		i;
	int		result;

	i = 0;
	while (i < rules->n_philos)
	{
		if ((rules->n_philos % 2 == 0 && turn % 2 == 0)
			|| (rules->n_philos % 2 != 0 && i < turn && turn % 2 == 0))
			result = even_turn(turn, i);
		else if ((rules->n_philos % 2 == 0 && turn % 2 != 0)
			|| (rules->n_philos % 2 != 0 && i < turn && turn % 2 != 0))
			result = odd_turn(turn, i);
		else if (rules->n_philos % 2 != 0 && i == turn)
			result = 0;
		else if (rules->n_philos % 2 != 0 && i > turn && turn % 2 == 0)
			result = odd_turn(turn + 1, i);
		else if (rules->n_philos % 2 != 0 && i > turn && turn % 2 != 0)
			result = even_turn(turn + 1, i);
		set_turn(&rules->philos_arg[i], result);
		i++;
	}
}
