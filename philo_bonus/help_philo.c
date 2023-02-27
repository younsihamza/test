/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:31:45 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/27 18:27:49 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argument(t_var *v)
{
	if (check_arg(v->argv) != 0)
		return (1);
	v->number_of_philosopher = ft_atoi(v->argv[1]);
	v->time_to_die = ft_atoi(v->argv[2]);
	v->time_to_eat = ft_atoi(v->argv[3]);
	v->time_to_sleep = ft_atoi(v->argv[4]);
	return (0);
}

void	get_fork(t_ph *phi)
{
	struct timeval	time;

	sem_wait(phi->forks);
	gettimeofday(&time, NULL);
	sem_wait(phi->print);
	printf("%ld ms philosopher %d has taken a fork\n",
		((time.tv_sec * 1000000 + time.tv_usec - phi->start_time) / 1000),
		phi->i +1);
	sem_post(phi->print);
	sem_wait(phi->forks);
	gettimeofday(&time, NULL);
	sem_wait(phi->print);
	printf("%ld ms philosopher %d has taken a fork\n",
		((time.tv_sec * 1000000 + time.tv_usec - phi->start_time) / 1000),
		phi->i +1);
	sem_post(phi->print);
}

void	eat(t_ph *phi)
{
	struct timeval	time;
	long			tmp;

	gettimeofday(&time, NULL);
	tmp = time.tv_sec * 1000000 + time.tv_usec;
	phi->number_of_time_eat++;
	sem_wait(phi->print);
	printf("%ld ms philosopher %d is eating\n", ((time.tv_sec * 1000000
				+ time.tv_usec - phi->start_time) / 1000), phi->i + 1);
	sem_post(phi->print);
	while (((time.tv_sec * 1000000 + time.tv_usec - tmp) / 1000)
		< phi->time_to_eat)
	{
		usleep(1000);
		gettimeofday(&time, NULL);
	}
}

void	put_fork(t_ph *phi)
{
	sem_post(phi->forks);
	sem_post(phi->forks);
}

void	ft_sleep(t_ph *phi)
{
	struct timeval	time;
	long			tmp;

	gettimeofday(&time, NULL);
	tmp = (time.tv_sec * 1000000) + time.tv_usec;
	sem_wait(phi->print);
	printf("%ld ms philosopher %d is sleeing\n", ((time.tv_sec * 1000000
				+ time.tv_usec - phi->start_time) / 1000), phi->i + 1);
	sem_post(phi->print);
	while (((time.tv_sec * 1000000 + time.tv_usec - tmp)
			/ 1000) < phi->time_to_sleep)
	{
		usleep(1000);
		gettimeofday(&time, NULL);
	}
}
