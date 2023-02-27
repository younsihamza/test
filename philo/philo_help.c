/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:26:55 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/27 13:27:01 by hyounsi          ###   ########.fr       */
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
	pthread_mutex_lock(&p->print[0]);
	printf("%ld ms philosopher %d has taken a fork\n", time, p->i + 1);
	pthread_mutex_unlock(&p->print[0]);
	pthread_mutex_lock(&p->fork[(p->i + 1) % p->number_of_philo]);
	gettimeofday(&end, NULL);
	time = ((end.tv_sec * 1000000 + end.tv_usec - p->start) / 1000);
	pthread_mutex_lock(&p->print[0]);
	printf("%ld ms philosopher %d has taken a fork\n",
		time, p->i + 1);
	pthread_mutex_unlock(&p->print[0]);
}

int	test_dead(t_ph *p)
{
	struct timeval	end;
	long			time;

	gettimeofday(&end, NULL);
	time = end.tv_sec * 1000000 + end.tv_usec;
	if ((time - p->last_time_eat) / 1000 > p->time_to_dia)
	{
		pthread_mutex_lock(&p->print[0]);
		printf("%ld ms philosopher %d died\n",
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
	pthread_mutex_unlock(&p->fork[(p->i + 1) % p->number_of_philo]);
	gettimeofday(&end, NULL);
	time = end.tv_sec * 1000000 + end.tv_usec;
}

void	eat(t_ph *p)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	pthread_mutex_lock(&p->print[0]);
	printf("%ld ms philosopher %d is eating \n",
		((end.tv_sec * 1000000 + end.tv_usec - p->start) / 1000), p->i + 1);
	pthread_mutex_unlock(&p->print[0]);
	p->number_of_time_to_eat += 1;
	p->last_time_eat = end.tv_sec * 1000000 + end.tv_usec;
	sleep_time(p->time_to_eat);
}

void	ft_sleep(t_ph *p)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	pthread_mutex_lock(&p->print[0]);
	printf("%ld ms philosopher %d is sleeping \n",
		((end.tv_sec * 1000000 + end.tv_usec - p->start) / 1000), p->i + 1);
	pthread_mutex_unlock(&p->print[0]);
	sleep_time(p->time_to_sleep);
}
