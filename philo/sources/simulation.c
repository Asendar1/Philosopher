/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:30:22 by hassende          #+#    #+#             */
/*   Updated: 2024/12/28 21:05:12 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->param->start_mutex);
		if (philo->param->start_simulation)
		{
			pthread_mutex_unlock(&philo->param->start_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->param->start_mutex);
		usleep(100);
	}
	return (NULL);
}

int	table_start(t_param *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->start_mutex);
	table->start_simulation = 0;
	pthread_mutex_unlock(&table->start_mutex);

	if (!table->meal_limit)
		return (0);
	if (table->philo_nb == 1)
		//TODO return (lonly_philo());
	while (++i < table->philo_nb)
		if (pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]))
			return (1);
	pthread_mutex_lock(&table->start_mutex);
	table->start_simulation = 1;
	pthread_mutex_unlock(&table->start_mutex);
	return (0);
}
