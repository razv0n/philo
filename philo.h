#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ulimit.h>
#include <sys/time.h> // dont forget to remove unsed header file
#include <unistd.h>
#define ARG_ERR "number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef enum{
    EAT,
    SLP,
    DEID,
    THK,
    TAK
}e_action;

typedef struct t_info 
{
    int         av;
    // int         philo_index;
    int         nm_philo;
    pthread_mutex_t print_lock;
    pthread_mutex_t access_lock;
    pthread_mutex_t died_lock;
    int         tm_to_die;
    int         tm_to_eat;
    int         tm_to_sleep;
    int         nm_meals;
    long        start_time;
    bool        died;
    char *str[5];
}t_info_all;


typedef struct thread
{
    pthread_t       philo_id;
    int             philo_index;
    int             l_fork;
    int             r_fork;
    long            last_meal;
    pthread_mutex_t fork;
    t_info_all      *info;
    struct thread   *philo_info;
} t_threads;

void    start_philo(t_info_all *info);
void init_strings(t_info_all *info);