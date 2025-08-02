/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:54:16 by mfahmi            #+#    #+#             */
/*   Updated: 2025/08/03 00:54:54 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h> // dont forget to remove unsed header file
# include <ulimit.h>
# include <unistd.h>
# define ARG_ERR "number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef enum e_action
{
	EAT,
	SLP,
	DEID,
	THK,
	TAK
}					e_action;

typedef enum e_return
{
	FAIL = 0,
	SUCCESS,
} e_return ;

typedef struct t_info
{
	int				av;
	int				nm_philo;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	access_lock;
	pthread_mutex_t	died_lock;
	pthread_mutex_t	meal_lock;
	pthread_t		monitor;
	int				tm_to_die;
	int				tm_to_eat;
	int				tm_to_sleep;
	int				nm_meals;
	long			start_time;
	bool			died;
	char			*str[5];
	bool			meal_lock_destroy;
	bool			died_lock_destroy;
	bool			access_lock_destroy;
	bool			print_lock_destroy;
}					t_info_all;

typedef struct thread
{
	pthread_t		philo_id;
	int				philo_index;
	bool			fork_destroy;
	int				l_fork;
	int				r_fork;
	long			last_meal;
	pthread_mutex_t	fork;
	int				eat_meal;
	t_info_all		*info;
	struct thread	*philo_info;
}					t_threads;

t_threads			*start_philo(t_info_all *info);
void				init_strings(t_info_all *info);
e_return(wait_philo(t_threads *philo));
e_return(run_philo(t_threads *philo));
void				*monitor_fun(void *ptr_philo);
void				*routine(void *s);
bool				start_pars(int ac);
void				print_do_action(char *action, t_threads *philo);
bool				init_info(int ac, char **av, t_info_all *info);
void				take_fork(t_threads *philo);
void				put_fork(t_threads *philo);
int					ft_strcmp(char *str1, char *str2);
long				time_fun(void);
void				philo_eating(char *action, t_threads *philo);
void				philo_thinking(char *action, t_threads *philo);
void				philo_sleeping(char *action, t_threads *philo);

#endif