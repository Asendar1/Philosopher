/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:30:22 by hassende          #+#    #+#             */
/*   Updated: 2024/12/29 17:43:33 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_simulation_start(t_philo *philo)
{
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
}

static void	think(t_philo *philo)
{
	write_handle(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	write_handle(FORK, philo);
	pthread_mutex_lock(&philo->left_fork->mutex);
	write_handle(FORK, philo);
	write_handle(EATING, philo);
	philo->meals_counter++;
	usleep(philo->param->t2e);
	if (philo->param->meal_limit != -1 && philo->meals_counter == philo->param->meal_limit)
		philo->full = 1;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

int	check_death(t_philo *philo)
{
	long current_time;

	current_time = get_time();
	if (current_time - philo->last_meal > philo->param->t2d)
	{
		pthread_mutex_lock(&philo->param->death_lock);
		philo->param->end = 1;
		write_handle(DEAD, philo);
		return (1);
	}
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_for_simulation_start(philo);
	philo->last_meal = get_time();
	while (simulation_finished(philo->param))
	{
		if (philo->full || check_death(philo))
			break;
		eat(philo);
		write_handle(SLEEPING, philo);
		usleep(philo->param->t2s);
		think(philo);
	}
	return (NULL);
}

int	table_start(t_param *table)
{
	int	i;

	i = -1;
	table->start_simulation = 0;
	if (!table->meal_limit)
		return (0);
	// if (table->philo_nb == 1)
		// TODO return (lonly_philo());
	pthread_create(&table->monitor, NULL, monitor_dinner, table);
	while (++i < table->philo_nb)
		if (pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]))
			return (1);
	pthread_mutex_lock(&table->start_mutex);
	table->start_simulation = 1;
	pthread_mutex_unlock(&table->start_mutex);
	i = -1;
	while (++i < table->philo_nb)
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
	pthread_join(table->monitor, NULL);
	return (0);
}
