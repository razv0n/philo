/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:33:24 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/26 21:45:29 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    if(!str1 || !str2)
        return (-1);
    while(str1[i] == str2[i] && str1[i] && str2[i])
        i++;
    return (str1[i] - str2[i]);
}

long    time_fun()
{
    struct timeval time;
    
    if (gettimeofday(&time, NULL))
        return (-1);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    print_action(long time, char *action, t_threads *philo)
{
    bool    died_help;

    died_help = false;
    if (philo->info->died_lock.__data.__lock != 0)
        pthread_mutex_lock(&philo->info->died_lock);
    if (!philo->info->died)
    {
        pthread_mutex_lock(&philo->info->print_lock);
        printf("%ld %d %s\n",time, philo->philo_index, action);
        pthread_mutex_unlock(&philo->info->print_lock);
        if (!ft_strcmp(action, philo->info->str[SLP]))
        {
            if (philo->info->tm_to_die < philo->info->tm_to_sleep + (time_fun() - philo->last_meal))
                died_help = true;
            else
                usleep(philo->info->tm_to_sleep * 1000);
        }
        else if (!ft_strcmp(action, philo->info->str[EAT]))
        {
             if (philo->info->tm_to_die < philo->info->tm_to_eat)
                died_help = true;
            else
            {
                pthread_mutex_lock(&philo->info->access_lock);
                philo->last_meal = time_fun();
                pthread_mutex_unlock(&philo->info->access_lock);
                usleep(philo->info->tm_to_eat * 1000);
            }
        }
         else if (philo->philo_index % 2 != 0 && !ft_strcmp(action, philo->info->str[THK]))
         {
            if (philo->info->tm_to_eat >= philo->info->tm_to_sleep)
                usleep((philo->info->tm_to_eat - philo->info->tm_to_sleep + 10) * 1000);
         }
    }
    else
    {
    if (philo->info->died_lock.__data.__lock != 0)
        pthread_mutex_unlock(&philo->info->died_lock);
        return;
    }
    if (philo->info->died_lock.__data.__lock != 0)
        pthread_mutex_unlock(&philo->info->died_lock);
    if (philo->info->tm_to_die <= time_fun() - philo->last_meal || died_help)
    {
        pthread_mutex_lock(&philo->info->died_lock);
        if (!philo->info->died)
        {
            philo->info->died = true;
            if (died_help)
                printf("%d %d %s\n",philo->info->tm_to_die , philo->philo_index, philo->info->str[DEID]);
            else
                printf("%ld %d %s\n",time_fun() - philo->info->start_time, philo->philo_index, philo->info->str[DEID]);
        }
        pthread_mutex_unlock(&philo->info->died_lock);
    }
}
void    mutex_forks(t_threads *philo)
{
    if (philo->philo_index == philo->info->nm_philo)
    {
        pthread_mutex_lock(&philo->philo_info[philo->r_fork].fork);
        printf("%ld %d %s\n",time_fun() - philo->info->start_time, philo->philo_index ,philo->info->str[TAK]);
        pthread_mutex_lock(&philo->philo_info[philo->l_fork].fork);
        printf("%ld %d %s\n",time_fun() - philo->info->start_time, philo->philo_index ,philo->info->str[TAK]);
    }
    else
    {
        pthread_mutex_lock(&philo->philo_info[philo->l_fork].fork);
        printf("%ld %d %s\n",time_fun() - philo->info->start_time, philo->philo_index ,philo->info->str[TAK]);
        pthread_mutex_lock(&philo->philo_info[philo->r_fork].fork);
        printf("%ld %d %s\n",time_fun() - philo->info->start_time, philo->philo_index ,philo->info->str[TAK]);
    }
    // print_action(time_fun() - philo->info->start_time, philo->info->str[TAK], philo); // TODO change it
    // print_action(time_fun() - philo->info->start_time, philo->info->str[TAK], philo);
    print_action(time_fun() - philo->info->start_time, philo->info->str[EAT], philo);
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
    print_action(time_fun() - philo->info->start_time, philo->info->str[SLP], philo);
    print_action(time_fun() - philo->info->start_time, philo->info->str[THK], philo);
}

void    *routine(void *s)
{
    t_threads *philo;
    
    philo = (t_threads*)s;
    if (philo->philo_index % 2 != 0)
        usleep(1000);
    // pthread_mutex_lock(&lock);
    // printf("%d\n", info->philo_index);
    // pthread_mutex_lock(&lock);

    while(1)
    {
        // pthread_mutex_lock(&philo->info->died_lock);
        if (philo->info->died)
            break;
        // pthread_mutex_unlock(&philo->info->died_lock);
        mutex_forks(philo);
        // break;
    }
    pthread_mutex_unlock(&philo->info->died_lock);
    usleep(1000);
    return (NULL);
}

void    take_forks(t_threads *philo, int i)
{
        philo->philo_info[i].l_fork = philo->philo_info[i].philo_index - 1;
        philo->philo_info[i].r_fork = philo->philo_info[(i + 1) % philo->info->nm_philo].philo_index - 1;
}

void    start_philo(t_info_all *info)
{
    int i;
    t_threads philo;

    philo.info = info;
    philo.philo_info = malloc(sizeof(t_threads) * philo.info->nm_philo);
    if (!philo.philo_info)
        return;
    i = 0;
    pthread_mutex_init(&philo.info->access_lock, NULL);
    pthread_mutex_init(&philo.info->print_lock, NULL);
    pthread_mutex_init(&philo.info->died_lock, NULL);
    while (i < philo.info->nm_philo)
    {
        philo.philo_info[i].info = info;
        philo.philo_info[i].philo_index = i + 1;
        philo.philo_info[i].philo_info = philo.philo_info;
        pthread_mutex_init(&philo.philo_info[i].fork, NULL);
        i++;
    }
    i = 0;
    while(i < philo.info->nm_philo)
    {
        take_forks(&philo, i);
        i++;
    }
    i = 0;
    philo.info->start_time = time_fun();
    while(i < philo.info->nm_philo)
    {
        // info->philo_index = i;
        philo.philo_info[i].last_meal = philo.info->start_time;
        pthread_create(&philo.philo_info[i].philo_id, NULL , routine, &philo.philo_info[i]);
            // return;
        i++;
    }
    i = 0;
    while(i < philo.info->nm_philo)
    {
        pthread_join(philo.philo_info[i].philo_id, NULL);
            // return;
        i++;
    }
}
