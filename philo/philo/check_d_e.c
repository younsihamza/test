/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_d_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:55:25 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/23 14:48:01 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_d_e(t_var *v, int argc)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < v->number_of_philosopher)
		{
			if (test_dead(&v->phi[i]) == 1)
				return (1);
			if (argc == 6)
			{
				if (v->phi[i].number_of_time_to_eat >= \
					v->number_of_time_to_eat)
					j++;
				if (j == v->number_of_philosopher)
					return (1);
			}
			i++;
		}
	}
	return (0);
}

int	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("argument not valide\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	sleep_time(int time)
{
	struct timeval	end;
	long			g;

	gettimeofday(&end, NULL);
	g = (end.tv_sec * 1000000 + end.tv_usec);
	while ((end.tv_sec * 1000000 + end.tv_usec - g) / 1000 < time)
	{
		usleep(1 * 1000);
		gettimeofday(&end, NULL);
	}
}
