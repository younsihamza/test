/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:13:37 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/27 17:47:15 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct philo
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_time_eat;
	int			number_of_philosopher;
	int			number_time_to_eat;
	long		last_time_eat;
	int			max_time_to_eat;
	int			i;
	int			argc;
	pthread_t	p;
	long		start_time;
	sem_t		*forks;
	sem_t		*print;
}t_ph;

typedef struct var
{
	int				number_of_time_to_eat;
	int				number_of_philosopher;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	char			**argv;
	long			hold;
	int				id;
	int				argc;
	int				*ids;
	sem_t			*forks;
	sem_t			*print;
	t_ph			*phi;
	struct timeval	start;
}t_var;

int		ft_atoi(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
int		check_arg(char **argv);
void	put_fork(t_ph *phi);
void	eat(t_ph *phi);
void	get_fork(t_ph *phi);
int		argument(t_var *v);
void	ft_sleep(t_ph *phi);
#endif