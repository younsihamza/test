/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:56:45 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/23 14:46:18 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>

typedef struct ph
{
	pthread_t		philo;
	long			start;
	int				number_of_time_to_eat;
	int				n;
	int				number_of_philo;
	int				time_to_dia;
	long			last_time_eat;
	int				time_to_eat;
	int				time_to_sleep;
	int				argc;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	int				i;
}t_ph;

typedef struct var
{
	int				number_of_time_to_eat;
	int				number_of_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	char			**argv;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	struct timeval	start;
	t_ph			*phi;
	long			hold;
}t_var;

int		ft_atoi(const char *str);
void	get_forks(t_ph *p);
int		test_dead(t_ph *p);
void	put_forks(t_ph *p);
void	eat(t_ph *p);
void	ft_sleep(t_ph *p);
int		check_d_e(t_var *v, int argc);
int		check_arg(char **argv);
void	sleep_time(int time);
#endif