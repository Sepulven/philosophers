/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:34:29 by asepulve          #+#    #+#             */
/*   Updated: 2023/11/25 17:33:38 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	kill_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		if (i != rules->philo_that_died)
			kill(rules->philos[i], SIGTERM);
		i++;
	}
}

void	*manager(void *arg)
{
	t_philo	*philo;
	int		status;

	philo = (t_philo *)arg;
	waitpid(philo->rules->philos[philo->id], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	sem_wait(philo->rules->rules_sem);
	if (status == 0)
	{
		philo->rules->n_philos_ate++;
		if (philo->rules->n_philos_ate != philo->rules->n_philos)
			print_message(philo, THINK_MSG);
	}
	else if (status == 1 && philo->rules->died == 0)
	{
		print_message(&philo->rules->philos_arg[philo->id], DIE_MSG);
		philo->rules->philo_that_died = philo->id;
		philo->rules->died = 1;
	}
	sem_post(philo->rules->rules_sem);
	return (NULL);
}
