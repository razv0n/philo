/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:33:24 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/29 12:37:45 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    put_fork(t_threads *philo)
{
     if (philo->philo_index == philo->info->nm_philo)
    {
        pthread_mutex_unlock(&philo->philo_info[philo->r_fork].fork);
        pthread_mutex_unlock(&philo->philo_info[philo->l_fork].fork);
    }
    else 
    {
        pthread_mutex_unlock(&philo->philo_info[philo->l_fork].fork);
        pthread_mutex_unlock(&philo->philo_info[philo->r_fork].fork);
    }
}

void    take_fork(t_threads *philo)
{
    if (philo->philo_index == philo->info->nm_philo)
    {
        pthread_mutex_lock(&philo->philo_info[philo->r_fork].fork);
        print_action(philo->info->str[TAK], philo);
        pthread_mutex_lock(&philo->philo_info[philo->l_fork].fork);
        print_action(philo->info->str[TAK], philo);
    }
    else
    {
        pthread_mutex_lock(&philo->philo_info[philo->l_fork].fork);
        print_action( philo->info->str[TAK], philo);
        pthread_mutex_lock(&philo->philo_info[philo->r_fork].fork);
        print_action( philo->info->str[TAK], philo);
    }
}

void    init_forks(t_threads *philo, int i)
{
        philo->philo_info[i].l_fork = philo->philo_info[i].philo_index - 1;
        philo->philo_info[i].r_fork = philo->philo_info[(i + 1) % philo->info->nm_philo].philo_index - 1;
}


e_return    start_philo_2(t_threads *philo)
{
    int i;

    i = 0;
    philo->info->start_time = time_fun();
    while(i < philo->info->nm_philo)
    {
        init_forks(philo, i);
        i++;
    }
    if (run_philo(philo) == FAIL)
        return (FAIL);
    if (wait_philo(philo) == FAIL)
        return (FAIL);
    return (SUCCESS);
}    

bool    init_mutex(t_threads *philo)
{
    if (pthread_mutex_init(&philo->info->access_lock, NULL))
    {
        philo->info->access_lock_destroy = true;           
        return (false);
    }
    if (pthread_mutex_init(&philo->info->print_lock, NULL))
    {
        philo->info->print_lock_destroy = true;
        return (false);
    }
    if (pthread_mutex_init(&philo->info->died_lock, NULL))
    {
        philo->info->died_lock_destroy = true;
        return (false);
    }
    if (pthread_mutex_init(&philo->info->meal_lock, NULL))
    {
        philo->info->meal_lock_destroy = true;
        return (false);
    }
    retunr (true);
}

t_threads   *start_philo(t_info_all *info)
{
    int i;
    t_threads philo;

    philo.info = info;
    philo.philo_info = malloc(sizeof(t_threads) * philo.info->nm_philo);
    if (!philo.philo_info)
        return (NULL);
    memset(philo.philo_info, 0, sizeof(t_threads) * philo.info->nm_philo);
    i = 0;
    if (!init_mutex(&philo))
        return (philo.philo_info);
    while (i < philo.info->nm_philo)
    {
        philo.philo_info[i].info = info;
        philo.philo_info[i].philo_index = i + 1;
        philo.philo_info[i].philo_info = philo.philo_info;
        if (pthread_mutex_init(&philo.philo_info[i].fork, NULL))
        {
            philo.philo_info[i].fork_destroy = true;
            return (philo.philo_info);
        }
        i++;
    }
    if (start_philo_2(&philo) == FAIL)
        return (philo.philo_info);
    return (philo.philo_info);
}
