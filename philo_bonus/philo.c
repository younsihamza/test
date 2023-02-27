/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:47:32 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/27 18:27:39 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test(t_ph *phi)
{
	struct timeval	end;
	int				i;

	i = 0;
	if (phi->i % 2)
		usleep(500);
	while (1)
	{
		get_fork(phi);
		gettimeofday(&end, NULL);
		phi->last_time_eat = end.tv_sec * 1000000 + end.tv_usec;
		eat(phi);
		put_fork(phi);
		ft_sleep(phi);
		gettimeofday(&end, NULL);
		sem_wait(phi->print);
		printf("%ld ms philosopher %d is thinking\n", (end.tv_sec * 1000000
				+ end.tv_usec - phi->start_time) / 1000, phi->i + 1);
		sem_post(phi->print);
	}
}

void	todo(t_ph *phi)
{
	struct timeval	ends;

	pthread_create(&phi->p, NULL, (void *)test, phi);
	pthread_detach(phi->p);
	gettimeofday(&ends, NULL);
	phi->last_time_eat = ends.tv_sec * 1000000 + ends.tv_usec ;
	while (1)
	{
		gettimeofday(&ends, NULL);
		if (((ends.tv_sec * 1000000 + ends.tv_usec - phi->last_time_eat)
				/ 1000) > phi->time_to_die)
		{
			sem_wait(phi->print);
			printf("%ld ms philosopher %d died\n", (ends.tv_sec * 1000000
					+ ends.tv_usec - phi->start_time) / 1000, phi->i + 1);
			exit(0);
		}
		if (phi->argc == 6)
			if (phi->number_of_time_eat > phi->max_time_to_eat)
				exit(0);
	}
}

int	alloc_init(t_var *v)
{
	int	i;

	i = 0;
	v->phi = malloc(sizeof(t_ph) * v->number_of_philosopher);
	v->ids = malloc(sizeof(int) * v->number_of_philosopher);
	v->forks = sem_open("forks", O_CREAT, 0644, v->number_of_philosopher);
	if (!v->phi || !v->ids || v->forks == SEM_FAILED)
		return (printf("ERORR\n"));
	gettimeofday(&v->start, NULL);
	v->hold = v->start.tv_sec * 1000000 + v->start.tv_usec;
	while (i < v->number_of_philosopher)
	{
		v->phi[i].time_to_die = v->time_to_die;
		v->phi[i].time_to_eat = v->time_to_eat;
		v->phi[i].time_to_sleep = v->time_to_sleep;
		v->phi[i].number_of_philosopher = v->number_of_philosopher;
		v->phi[i].start_time = v->hold;
		v->phi[i].i = i;
		v->phi[i].print = v->print;
		v->phi[i].forks = v->forks;
		v->phi[i].number_of_time_eat = 0;
		v->phi[i].argc = v->argc;
		v->phi[i++].max_time_to_eat = v->number_of_time_to_eat;
	}
	return (0);
}

void	create_process(t_var *v)
{
	int	i;

	i = 0;
	while (i < v->number_of_philosopher)
	{
		v->id = fork();
		if (v->id < 0)
			return ;
		if (v->id == 0)
			todo(&v->phi[i]);
		else
			v->ids[i] = v->id;
		i++;
	}
	waitpid(-1, NULL, 0);
	free(v->phi);
	free(v->ids);
	sem_unlink("forks");
	sem_unlink("print");
	i = 0;
	while (i < v->number_of_philosopher)
		kill(v->ids[i++], SIGKILL);
}

int	main(int argc, char **argv)
{
	t_var	v;

	sem_unlink("forks");
	sem_unlink("print");
	v.argc = argc;
	if (argc != 5 && argc != 6)
		return (printf("no valide argument\n"));
	if (argc == 6)
		v.number_of_time_to_eat = ft_atoi(argv[5]);
	v.argv = argv;
	if (argument(&v) != 0)
		return (printf("no valide argument\n"));
	v.print = sem_open("print", O_CREAT, 0644, 1);
	if (v.print == SEM_FAILED)
		return (0);
	if (alloc_init(&v) != 0)
		return (0);
	create_process(&v);
}
