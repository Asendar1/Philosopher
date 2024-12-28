/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:03:13 by hassende          #+#    #+#             */
/*   Updated: 2024/12/28 20:54:47 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_table(t_param *table)
{
	int i;

	i = -1;
	while (++i < table->philo_nb)
		pthread_mutex_destroy(&table->forks[i].mutex);
	free(table->forks);
	free(table->philos);
}

int	main(int argc, char *argv[])
{
	t_param	param;

	if (argc < 5 || argc > 6 || !check_input(argv))
	{
		write (2, "wrong input\n", 13);
		return (1);
	}
	init_param(&param, argv);
	table_init(&param);
	table_start(&param);
	clean_table(&param);
	return (0);
}
