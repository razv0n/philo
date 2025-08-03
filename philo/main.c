/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:17:27 by mfahmi            #+#    #+#             */
/*   Updated: 2025/08/03 14:13:10 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeping(char *action, t_threads *philo)
{
	if (!ft_strcmp(action, philo->info->str[SLP]))
		usleep(philo->info->tm_to_sleep * 1000);
}

void	one_philo(t_info_all *info)
{
	info->start_time = time_fun();
	printf("%ld %d %s\n", time_fun() - info->start_time, info->nm_philo,
		info->str[TAK]);
	printf("%d %d %s\n", info->tm_to_die, info->nm_philo, info->str[DEID]);
}

void	clean_up_mutex(t_threads *philo)
{
	int	i;

	i = 0;
	if (!philo->info->meal_lock_destroy)
		pthread_mutex_destroy(&philo->info->meal_lock);
	if (!philo->info->died_lock_destroy)
		pthread_mutex_destroy(&philo->info->died_lock);
	if (!philo->info->access_lock_destroy)
		pthread_mutex_destroy(&philo->info->access_lock);
	if (!philo->info->print_lock_destroy)
		pthread_mutex_destroy(&philo->info->print_lock);
	while (i < philo->info->nm_philo)
	{
		if (!philo->philo_info[i].fork_destroy)
			pthread_mutex_destroy(&philo->philo_info[i].fork);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_info_all	info;
	t_threads	*philo;

	memset(&info, 0, sizeof(t_info_all));
	if (!start_pars(ac) || !init_info(ac, av, &info))
		return (1);
	if (info.nm_philo == 1)
	{
		one_philo(&info);
		return (0);
	}
	philo = start_philo(&info);
	clean_up_mutex(philo);
	free(philo);
}
