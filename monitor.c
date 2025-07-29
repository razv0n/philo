/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:23:01 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/29 11:27:45 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
