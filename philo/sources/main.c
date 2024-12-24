/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:42:50 by hassende          #+#    #+#             */
/*   Updated: 2024/12/24 23:00:46 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_params *params, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * params->nb_philo);
	if (!*philos)
		return ;
	while (i < params->nb_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].params = params;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_params	*params;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
	{
		write(1, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	params = malloc(sizeof(t_params));
	if (!params)
		return (1);
	parge_args(argc, argv, params);
	init_philos(params, &philos);
	init_threads(params, philos);
	free(philos);
	free(params);
	return (0);
}
