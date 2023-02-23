/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:13:37 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/21 16:02:01 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>
 #include <signal.h>
 #include <mlx.h>

int	ft_atoi(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
#endif