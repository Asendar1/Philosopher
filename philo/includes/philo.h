/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:49:08 by hassende          #+#    #+#             */
/*   Updated: 2024/12/28 21:03:15 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_param	t_param;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				fork_id;
}				t_fork;

typedef struct s_philo
{
	int				id;
	int				full;
	long			meals_counter;
	long			last_meal;
	t_fork			*right_fork;
	t_fork			*left_fork;
	pthread_t		thread;
	t_param			*param;
}				t_philo;

typedef struct s_param
{
	int				philo_nb;
	int				t2d;
	int				t2s;
	int				t2e;
	int				meal_limit;
	int				end;
	int				start_simulation;
	long			start_time;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t print_lock;
	pthread_mutex_t death_lock;
	pthread_mutex_t	start_mutex;
}				t_param;

void		init_param(t_param *param, char *argv[]);
void		table_init(t_param *table);
void		clean_table(t_param *table);
void		*routine(void *data);
void		eat_routine(t_philo *philo);
void		lonly_philo(t_philo *philo);
void		print_status(t_philo *philo, char *status);
int			check_input(char **argv);
int			check_death(t_philo *philo);
int			table_start(t_param *table);
long		get_time();
long int	ft_atoi(char *str);

#endif
