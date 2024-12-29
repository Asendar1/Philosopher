/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:09:38 by hassende          #+#    #+#             */
/*   Updated: 2024/12/29 17:25:22 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **argv)
{
	long	buffer;
	int		i;

	i = 1;
	while (argv[i])
	{
		buffer = ft_atoi(argv[i]);
		if (buffer == LONG_MAX)
			return (0);
		i++;
	}
	return (1);
}

void	write_handle(t_status status, t_philo *philo)
{
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->param->print_lock);
	if (status == FORK && simulation_finished(philo->param))
		printf("[%ld] philo %d has taken a fork\n", get_time() - philo->param->start_time, philo->id);
	else if (status == EATING && simulation_finished(philo->param))
	{
		printf("[%ld] philo %d is eating\n", get_time() - philo->param->start_time, philo->id);
		philo->last_meal = get_time();
	}
	else if (status == SLEEPING && simulation_finished(philo->param))
		printf("[%ld] philo %d is sleeping\n", get_time() - philo->param->start_time, philo->id);
	else if (status == THINKING && simulation_finished(philo->param))
		printf("[%ld] philo %d is thinking\n", get_time() - philo->param->start_time, philo->id);
	else if (status == DEAD)
	{
		printf("[%ld] philo %d died\n", get_time() - philo->param->start_time, philo->id);
		pthread_mutex_unlock(&philo->param->death_lock);
	}
	pthread_mutex_unlock(&philo->param->print_lock);
}

long	get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
