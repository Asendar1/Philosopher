/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:37:40 by hassende          #+#    #+#             */
/*   Updated: 2024/12/24 23:01:18 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	printf("[%ld] Philo[%d] is eating\n", time_now(), philo->id);
	usleep(philo->params->t2e * 1000);
}

void	philo_sleep(t_philo *philo)
{
	printf("[%ld] Philo[%d] is sleepin\n", time_now(), philo->id);
	usleep(philo->params->t2s * 1000);
}

void	philo_think(t_philo *philo)
{
	printf("[%ld] Philo[%d] is thinking\n", time_now(), philo->id);
	usleep(philo->params->t2s * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

void	init_threads(t_params *params, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < params->nb_philo)
	{
		pthread_create(&((philos + i)->thread), NULL, routine, philos + i);
		i++;
	}
	i = 0;
	while (i < params->nb_philo)
	{
		pthread_join((philos + i)-> thread, NULL);
		i++;
	}
}
