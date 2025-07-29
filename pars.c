/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:17:27 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/28 17:01:14 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

long    ft_atol(char    *s)
{
    long    res;
    int     i;
    
    i = 0;
    res = 0;
    while(s[i] && is_whitespace(s[i]))
        i++;
    if (s[i] == '+' || s[i] == '-')
    {
        if (s[i] == '-')    
            return(res);
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        res = res * 10 + s[i] - '0';
        if (res > 2147483647)
            return (0);
         i++;
    }
    return (res);
}

bool    start_pars(int ac)
{
    if (ac > 6 || ac < 5)      
    {
        printf("%s\n", ARG_ERR);
        return (false);
    }
    return (true);
}

bool    init_info(int ac, char **av, t_info_all *info)
{
    int     i;

    i = 0;
    info->nm_philo = -1;
    info->tm_to_die = -1;
    info->tm_to_eat = -1;
    info->nm_meals = -1;
    info->tm_to_sleep = -1;
    info->nm_philo = ft_atol(av[1]);
    info->tm_to_die = ft_atol(av[2]);
    info->tm_to_eat = ft_atol(av[3]);
    info->tm_to_sleep = ft_atol(av[4]);
    if (ac == 6)
        info->nm_meals = ft_atol(av[5]);
    info->died = false;
    if(!info->tm_to_sleep || !info->nm_philo || !info->tm_to_die || !info->tm_to_eat || !info->nm_meals)
       return (false);
    init_strings(info);
    return (true);
}

void init_strings(t_info_all *info)
{
    info->str[0] = "is eating";
    info->str[1] = "is sleeping";
    info->str[2] = "died";
    info->str[3] = "is thinking";
    info->str[4] = "has taken a fork";
}
