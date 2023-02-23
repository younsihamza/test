/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:26:55 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/23 13:39:26 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_ph *p)
{
	struct timeval	end;
	long			time;

	pthread_mutex_lock(&p->fork[p->i]);
	gettimeofday(&end, NULL);
	time = ((end.tv_sec * 1000000 + end.tv_usec - p->start) / 1000);
	printf("%ld ms philosopher %d get left fork %d\n", time, p->i + 1, p->i + 1);
	pthread_mutex_lock(&p->fork[(p->i + 1) % p->number_of_philo]);
	gettimeofday(&end, NULL);
	time = ((end.tv_sec * 1000000 + end.tv_usec - p->start) / 1000);
	printf("%ld ms philosopher %d get right fork %d\n",
		time, p->i + 1, (p->i + 1) % p->number_of_philo + 1);
}

int	test_dead(t_ph *p)
{
	struct timeval	end;
	long			time;

	gettimeofday(&end, NULL);
	time = end.tv_sec * 1000000 + end.tv_usec;
	if ((time - p->last_time_eat) / 1000 > p->time_to_dia)
	{
		printf("%ld ms philosopher %d is dead\n",
			(time - p->start) / 1000, p->i + 1);
		return (1);
	}
	return (0);
}

void	put_forks(t_ph *p)
{
	struct timeval	end;
	long			time;

	pthread_mutex_unlock(&p->fork[p->i]);
	gettimeofday(&end, NULL);
	time = end.tv_sec * 1000000 + end.tv_usec;
	printf("%ld ms philosopher %d put left fork %d\n",
		((time - p->start) / 1000), p->i + 1, p->i + 1);
	pthread_mutex_unlock(&p->fork[(p->i + 1) % p->number_of_philo]);
	gettimeofday(&end, NULL);
	time = end.tv_sec * 1000000 + end.tv_usec;
	printf("%ld ms philosopher %d put right fork %d\n",
		((time - p->start) / 1000), p->i + 1,
		(p->i + 1) % p->number_of_philo + 1);
}

void	eat(t_ph *p)
{
	struct timeval	end;
	long			g;

	gettimeofday(&end, NULL);
	g = (end.tv_sec * 1000000 + end.tv_usec);
	printf("%ld ms philosopher %d is eating \n",
		((end.tv_sec * 1000000 + end.tv_usec - p->start) / 1000), p->i + 1);
	p->number_of_time_to_eat += 1;
	p->last_time_eat = end.tv_sec * 1000000 + end.tv_usec;
	while ((end.tv_sec * 1000000 + end.tv_usec - g) / 1000 < p->time_to_eat)
	{
		usleep(1 * 1000);
		gettimeofday(&end, NULL);
	}
}

void	ft_sleep(t_ph *p)
{
	struct timeval	end;
	long			g;

	gettimeofday(&end, NULL);
	g = (end.tv_sec * 1000000 + end.tv_usec);
	printf("%ld ms philosopher %d is sleeping \n",
		((end.tv_sec * 1000000 + end.tv_usec - p->start) / 1000), p->i + 1);
	while ((end.tv_sec * 1000000 + end.tv_usec - g) / 1000 < p->time_to_sleep)
	{
		usleep(1 * 1000);
		gettimeofday(&end, NULL);
	}
}
