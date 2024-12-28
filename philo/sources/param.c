/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:05:01 by hassende          #+#    #+#             */
/*   Updated: 2024/12/28 20:55:36 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (15);
	while (str[i])
		i++;
	return (i);
}

long int	ft_atoi(char *str)
{
	int			i;
	int			neg;
	long int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (LONG_MAX);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	if (res > INT_MAX || res < INT_MIN || ft_strlen(str) > 10)
		return (LONG_MAX);
	return (res * neg);
}

void	init_param(t_param *param, char *argv[])
{
	param->philo_nb = ft_atoi(argv[1]);
	param->t2d = ft_atoi(argv[2]) * 1000;
	param->t2e = ft_atoi(argv[3]) * 1000;
	param->t2s = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		param->meal_limit = ft_atoi(argv[5]);
	else
		param->meal_limit = -1;
	param->start_time = get_time();
}
