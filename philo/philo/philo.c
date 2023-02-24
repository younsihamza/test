/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:28:15 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/23 14:47:41 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*todo(t_ph *p)
{
	struct timeval	end;

	if (p->i % 2)
		sleep_time(10);
	while (1)
	{
		get_forks(p);
		eat(p);
		put_forks(p);
		ft_sleep(p);
		gettimeofday(&end, NULL);
		pthread_mutex_lock(&p->print[0]);
		printf("%ld ms philosopher %d is thinking \n",
			((end.tv_sec * 1000000 + end.tv_usec - p->start) / 1000), p->i + 1);
		pthread_mutex_unlock(&p->print[0]);
	}
}

int	mutex_alloc(t_var *v)
{
	int	i;

	i = 0;
	v->phi = malloc(sizeof(t_ph) * v->number_of_philosopher);
	pthread_mutex_init(&v->print, NULL);
	v->fork = malloc(sizeof(pthread_mutex_t) * v->number_of_philosopher);
	if (!v->fork || !v->phi)
		return (1);
	while (i < v->number_of_philosopher)
	{
		if (pthread_mutex_init(&v->fork[i], NULL) != 0)
			return (write(2, "ERROR : mutex int feild\n", 24));
		v->phi[i].fork = v->fork;
		v->phi[i].print = &v->print;
		v->phi[i].number_of_time_to_eat = 0;
		v->phi[i].number_of_philo = v->number_of_philosopher;
		v->phi[i].i = i;
		v->phi[i].time_to_eat = v->time_to_eat;
		v->phi[i].time_to_sleep = v->time_to_sleep;
		v->phi[i].time_to_dia = v->time_to_die;
		v->phi[i].start = v->hold;
		v->phi[i].last_time_eat = v->hold;
		v->phi[i++].n = v->number_of_time_to_eat;
	}
	return (0);
}

int	create_thread_detach(t_var *v)
{
	int	i;

	i = 0;
	while (i < v->number_of_philosopher)
	{
		if (pthread_create(&v->phi[i].philo,
				NULL, (void *)todo, &v->phi[i]) != 0)
			return (write(2, "ERROR : thread create feild\n", 28));
		i++;
	}
	i = 0;
	while (i < v->number_of_philosopher)
	{
		if (pthread_detach(v->phi[i].philo) != 0)
			return (write(2, "ERROR : detach is feild\n", 21));
		i++;
	}
	return (0);
}

int	argument(t_var *v)
{
	if (check_arg(v->argv))
		return (1);
	v->time_to_sleep = ft_atoi(v->argv[4]);
	v->time_to_eat = ft_atoi(v->argv[3]);
	v->time_to_die = ft_atoi(v->argv[2]);
	v->number_of_philosopher = ft_atoi(v->argv[1]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	v;

	v.argv = argv;
	if (argc != 5 && argc != 6)
		return (0);
	if (argc == 6)
		v.number_of_time_to_eat = ft_atoi(argv[5]);
	if (argument(&v))
		return (0);
	if (v.number_of_philosopher <= 0)
		return (0);
	gettimeofday(&v.start, NULL);
	v.hold = v.start.tv_sec * 1000000 + v.start.tv_usec;
	if (mutex_alloc(&v) != 0)
		return (0);
	if (create_thread_detach(&v) != 0)
		return (0);
	check_d_e(&v, argc);
}
