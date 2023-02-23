/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:47:32 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/21 17:46:32 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct philo 
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_time_eat;
    int number_of_philosopher;
    int number_time_to_eat;
    long last_time_eat;
    int max_time_to_eat;
    int i;
    int argc;
    pthread_t pp;
    long start_time;
    sem_t *p;
}t_ph;

typedef struct var
{
    int number_of_time_to_eat;
    int number_of_philosopher;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    char **argv;
}t_var;

void argument(t_var *v)
{
    v->number_of_philosopher = ft_atoi(v->argv[1]);
    v->time_to_die = ft_atoi(v->argv[2]);
    v->time_to_eat = ft_atoi(v->argv[3]);
    v->time_to_sleep = ft_atoi(v->argv[4]);
}
void get_fork(t_ph *phi)
{
    struct timeval time;
    sem_wait(phi->p);
    gettimeofday(&time,NULL);
    printf("%ld ms philosopher %d get first fork \n",((time.tv_sec * 1000000 + time.tv_usec)/1000) - phi->start_time,phi->i);
    sem_wait(phi->p);
    gettimeofday(&time,NULL);
    printf("%ld ms philosopher %d get second fork\n",((time.tv_sec * 1000000 + time.tv_usec)/1000) - phi->start_time,phi->i);
}
void eat(t_ph *phi)
{
    struct timeval time;
    long tmp;
    gettimeofday(&time,NULL);
    tmp = time.tv_sec * 1000000 + time.tv_usec;
    phi->last_time_eat = tmp;
    phi->number_of_time_eat++;
    printf("%ld ms philosopher %d eating\n",((time.tv_sec * 1000000 + time.tv_usec)/1000) - phi->start_time,phi->i);
    while(((time.tv_sec * 1000000 + time.tv_usec - tmp)/1000) < phi->time_to_eat)
    {
        usleep(1000);
        gettimeofday(&time,NULL);
    }
}
void put_fork(t_ph *phi)
{
   struct timeval time; 
    sem_post(phi->p);
    gettimeofday(&time,NULL);
    printf("%ld ms philosopher %d put first fork\n",((time.tv_sec * 1000000 + time.tv_usec)/1000) - phi->start_time,phi->i);
    sem_post(phi->p);
    gettimeofday(&time,NULL);
    printf("%ld ms philosopher %d put second fork\n",((time.tv_sec * 1000000 + time.tv_usec)/1000) - phi->start_time,phi->i);
}
void ft_sleep(t_ph *phi)
{
    struct timeval time;
    long tmp;
    gettimeofday(&time,NULL);
    tmp =  (time.tv_sec * 1000000) + time.tv_usec;
    printf("%ld ms philosopher %d sleeing\n",((time.tv_sec * 1000000 + time.tv_usec)/1000) - phi->start_time,phi->i);
    while(((time.tv_sec * 1000000 + time.tv_usec - tmp)/1000) < phi->time_to_sleep)
    {
        usleep(1000);
        gettimeofday(&time,NULL);
    }
}
void  test(t_ph *phi)
{
    struct timeval courent;
    int i;
    while(1)
    {
        gettimeofday(&courent,NULL);
        //printf("hamza\n");
            if((((courent.tv_sec * 1000000 + courent.tv_usec) - phi->last_time_eat) / 1000) > phi->time_to_die)
            {
                printf("%ld ms philosopher %d dead-------\n",((courent.tv_sec * 1000000 + courent.tv_usec) - phi->start_time*1000) / 1000,phi->i);
                exit(0);
            }
            if(phi->argc == 6)
                {
                    if(phi->number_of_time_eat > phi->max_time_to_eat)
                        exit(0);
                }
            i++;
    }
}
void todo(t_ph *phi)
{
    struct timeval time;
    pthread_create(&phi->pp,NULL,(void*)test,phi);
    pthread_detach(phi->pp);
    if(phi->i%2)
            usleep(100);
           while(1)
            {
                get_fork(phi);
                eat(phi);
                put_fork(phi);
                ft_sleep(phi);
                gettimeofday(&time,NULL);
                printf("%ld ms philosopher %d thinking\n",((time.tv_sec * 1000000 + time.tv_usec)/1000) - phi->start_time,phi->i);
            }
}

int main(int argc, char **argv)
{
    int i = 0;
    int id;
    t_var v;
    int *ids;
    t_ph *phi;
    struct timeval start;
    if(argc != 5 && argc != 6)
        return(0);
    if(argc == 6)
        v.number_of_time_to_eat = ft_atoi(argv[5]);
    v.argv = argv;
    argument(&v);
    phi = malloc(sizeof(t_ph)*v.number_of_philosopher);
    ids = malloc(sizeof(int)*v.number_of_philosopher);
    sem_t *p;
    sem_unlink("fork");
    p = sem_open("fork",O_CREAT,0666,v.number_of_philosopher);
    gettimeofday(&start,NULL);
    while(i < v.number_of_philosopher)
    {
        phi[i].time_to_eat = v.time_to_eat;
        phi[i].time_to_die = v.time_to_die;
        phi[i].time_to_sleep = v.time_to_sleep;
        phi[i].number_of_philosopher = v.number_of_philosopher;
        phi[i].i = i;
        phi[i].p = p;
        phi[i].max_time_to_eat = v.number_of_time_to_eat;
        phi[i].number_of_time_eat = 0;
        phi[i].argc = argc;
        phi[i].start_time = (start.tv_sec * 1000000 + start.tv_usec) / 1000;
        phi[i].last_time_eat = (start.tv_sec * 1000000 + start.tv_usec);
        i++;
    }
    i = 0;
    while(i < v.number_of_philosopher)
    {
        id = fork();
        if(id == 0)
            todo(&phi[i]);
        else
            ids[i] = id;
        i++;
    }
    waitpid(-1,NULL,0);
    i = 0;
    while(i < v.number_of_philosopher)                                                     
    {
        kill(ids[i],SIGKILL);
        i++;
    }
    }  

