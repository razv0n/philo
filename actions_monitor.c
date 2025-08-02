/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:23:01 by mfahmi            #+#    #+#             */
/*   Updated: 2025/08/03 00:53:02 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeping(char *action, t_threads *philo)
{
	if (!ft_strcmp(action, philo->info->str[SLP]))
		usleep(philo->info->tm_to_sleep * 1000);
}

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

bool	monitor_meals(t_threads *philo, int i)
{
	static int	how_many_eat;

	if (philo->info->nm_meals != -1)
	{
		pthread_mutex_lock(&philo->info->meal_lock);
		if (philo->philo_info[i].eat_meal >= philo->info->nm_meals)
		{
			philo->philo_info[i].eat_meal = -1;
			how_many_eat++;
		}
		pthread_mutex_unlock(&philo->info->meal_lock);
		if (how_many_eat == philo->info->nm_philo)
		{
			pthread_mutex_lock(&philo->info->died_lock);
			philo->info->died = true;
			pthread_mutex_unlock(&philo->info->died_lock);
			return (false);
		}
	}
	return (true);
}

void	*monitor_fun(void *ptr_philo)
{
	t_threads	*philo;
	int			i;

	i = 0;
	philo = (t_threads *)ptr_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->info->access_lock);
		if (philo->info->tm_to_die <= time_fun()
			- philo->philo_info[i].last_meal)
		{
			pthread_mutex_unlock(&philo->info->access_lock);
			pthread_mutex_lock(&philo->info->died_lock);
			philo->info->died = true;
			pthread_mutex_unlock(&philo->info->died_lock);
			printf("%ld %d %s\n", time_fun() - philo->info->start_time,
				philo->philo_info[i].philo_index, "died");
			break ;
		}
		pthread_mutex_unlock(&philo->info->access_lock);
		if (monitor_meals(philo, i) == false)
			break ;
		i++;
		if (i == philo->info->nm_philo)
			i = 0;
		usleep(1);
	}
	return (NULL);
}
