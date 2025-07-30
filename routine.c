/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:24:33 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/30 23:26:37 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_fun(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_action(char *action, t_threads *philo)
{
	usleep(50);
	pthread_mutex_lock(&philo->info->print_lock);
	pthread_mutex_lock(&philo->info->died_lock);
	if (!philo->info->died)
		printf("%ld %d %s\n", time_fun() - philo->info->start_time,
			philo->philo_index, action);
	pthread_mutex_unlock(&philo->info->died_lock);
	pthread_mutex_unlock(&philo->info->print_lock);
	if (!ft_strcmp(action, philo->info->str[SLP]))
		usleep(philo->info->tm_to_sleep * 1000);
	else if (!ft_strcmp(action, philo->info->str[EAT]))
	{
		if (philo->info->nm_meals != -1)
		{
			pthread_mutex_lock(&philo->info->meal_lock);
			if (philo->eat_meal != -1)
				philo->eat_meal++;
			pthread_mutex_unlock(&philo->info->meal_lock);
		}
		pthread_mutex_lock(&philo->info->access_lock);
		philo->last_meal = time_fun();
		pthread_mutex_unlock(&philo->info->access_lock);
		usleep(philo->info->tm_to_eat * 1000);
	}
	else if (philo->info->nm_philo % 2 != 0 && !ft_strcmp(action,
			philo->info->str[THK]))
    	{
            if (philo->info->tm_to_eat >= philo->info->tm_to_sleep)
                usleep((philo->info->tm_to_eat - philo->info->tm_to_sleep + 5) * 1000);
        }
}

void	start_actions(t_threads *philo)
{
    take_fork(philo);
	print_action(philo->info->str[EAT], philo);
	put_fork(philo);
	print_action(philo->info->str[SLP], philo);
	print_action(philo->info->str[THK], philo);
}

void	*routine(void *s)
{
	t_threads	*philo;

	philo = (t_threads *)s;
	if (philo->philo_index % 2 != 0)
		usleep(3000);
	while (1)
	{
		pthread_mutex_lock(&philo->info->died_lock);
		if (philo->info->died)
			break ;
		pthread_mutex_unlock(&philo->info->died_lock);
		start_actions(philo);
	}
	pthread_mutex_unlock(&philo->info->died_lock);
	return (NULL);
}
