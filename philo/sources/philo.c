/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:45:35 by hassende          #+#    #+#             */
/*   Updated: 2024/12/28 21:04:32 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_param *table)
{
	int i;

	i = -1;
	while (++i < table->philo_nb)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = 0;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(i + 1) % table->philo_nb];
		if (table->philos[i].id % 2 == 0)
		{
			table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_nb];
			table->philos[i].left_fork = &table->forks[i];
		}
		table->philos[i].meals_counter = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].param = table;
	}
}

void	table_init(t_param *table)
{
	int	i;

	i = -1;
	table->end = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nb);
	table->forks = malloc(sizeof(t_fork) * table->philo_nb);
	while(++i > table->philo_nb)
	{
		pthread_mutex_init(&table->forks->mutex, NULL);
		table->forks->fork_id = i;
	}
	philo_init(table);
}