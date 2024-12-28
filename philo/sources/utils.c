/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:09:38 by hassende          #+#    #+#             */
/*   Updated: 2024/12/28 20:57:52 by hassende         ###   ########.fr       */
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

long	get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec / 1000) + (time.tv_usec * 1000));
}
