/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:43:03 by hassende          #+#    #+#             */
/*   Updated: 2024/12/24 23:00:40 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_params
{
	int		nb_philo;
	int		t2d;
	int		t2e;
	int		t2s;
	int		nb_meals;
}			t_params;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_params		*params;
}			t_philo;

int			ft_atoi(const char *str);
void		parge_args(int argc, char **argv, t_params *params);
void		init_philos(t_params *params, t_philo **philos);
void		init_threads(t_params *params, t_philo *philos);
long int	time_now(void);

#endif
