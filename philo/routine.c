/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:24:33 by mfahmi            #+#    #+#             */
/*   Updated: 2025/08/03 15:26:33 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(char *action, t_threads *philo)
{
	if (!ft_strcmp(action, philo->info->str[EAT]))
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
}

void	philo_thinking(char *action, t_threads *philo)
{
	if (philo->info->nm_philo % 2 != 0 && !ft_strcmp(action,
			philo->info->str[THK]))
	{
		if (philo->info->tm_to_eat > philo->info->tm_to_sleep)
			usleep((philo->info->tm_to_eat - philo->info->tm_to_sleep + 100)
				* 1000);
		else if (philo->info->tm_to_eat <= philo->info->tm_to_sleep)
			usleep(((philo->info->tm_to_eat * 2) - philo->info->tm_to_sleep)
				* 1000);
	}
	else
		usleep(70);
}

void	print_do_action(char *action, t_threads *philo)
{
	pthread_mutex_lock(&philo->info->print_lock);
	pthread_mutex_lock(&philo->info->died_lock);
	if (!philo->info->died)
		printf("%ld %d %s\n", time_fun() - philo->info->start_time,
			philo->philo_index, action);
	pthread_mutex_unlock(&philo->info->died_lock);
	pthread_mutex_unlock(&philo->info->print_lock);
	philo_sleeping(action, philo);
	philo_eating(action, philo);
	philo_thinking(action, philo);
}

void	start_actions(t_threads *philo)
{
	take_fork(philo);
	print_do_action(philo->info->str[EAT], philo);
	put_fork(philo);
	print_do_action(philo->info->str[SLP], philo);
	print_do_action(philo->info->str[THK], philo);
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
