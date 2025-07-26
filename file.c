#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
pthread_mutex_t lock;

void   *fun(void *s)
{
    static char a = 'a';
    pthread_mutex_lock(&lock);
    a++;
    write(1, &a, 1);
    write(1, "\n", 1); // data race
    pthread_mutex_unlock(&lock);
}

int main()
{
    // pthread_mutex_t lock;
    pthread_t philo1, philo2;

    if (pthread_mutex_init(&lock, NULL) != 0)
        perror(" ");
    pthread_create(&philo1, NULL, fun, NULL);
    pthread_create(&philo2, NULL, fun, NULL);

    pthread_join(philo1, NULL);
    pthread_join(philo2, NULL);
    return (0); 

}
