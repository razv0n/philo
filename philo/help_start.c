/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:21:25 by mfahmi            #+#    #+#             */
/*   Updated: 2025/08/03 14:15:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_return	run_philo(t_threads *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nm_philo)
	{
		philo->philo_info[i].last_meal = philo->info->start_time;
		philo->philo_info[i].eat_meal = 0;
		if (pthread_create(&philo->philo_info[i].philo_id, NULL, routine,
				&philo->philo_info[i]))
			return (FAIL);
		i++;
	}
	if (pthread_create(&philo->info->monitor, NULL, monitor_fun, philo))
		return (FAIL);
	return (SUCCESS);
}

t_return	wait_philo(t_threads *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nm_philo)
	{
		if (pthread_join(philo->philo_info[i].philo_id, NULL))
			return (FAIL);
		i++;
	}
	if (pthread_join(philo->info->monitor, NULL))
		return (FAIL);
	return (SUCCESS);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (-1);
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}
