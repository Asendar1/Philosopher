/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:33:09 by hassende          #+#    #+#             */
/*   Updated: 2024/12/29 22:40:29 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (NULL);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destory_all("Thread creation error", program, forks);
	i = -1;
	while (++i < program->philos[0].num_of_philos)
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destory_all("Thread creation error", program, forks);
	i = -1;
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", program, forks);
	while (++i < program->philos[0].num_of_philos)
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all("Thread join error", program, forks);
	return (0);
}
