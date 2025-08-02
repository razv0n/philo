/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:53:47 by mfahmi            #+#    #+#             */
/*   Updated: 2025/08/02 19:09:01 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*__________________simple_exaple________________*/

// pthread_mutex_t	lock;

// void	*fun(void *s)
// {
// 	static char	a = 'a';

// 	pthread_mutex_lock(&lock);
// 	a++;
// 	write(1, &a, 1);
// 	write(1, "\n", 1); // data race
// 	pthread_mutex_unlock(&lock);
// }

// int	main(void)
// {
// 	// pthread_mutex_t lock;
// 	pthread_t philo1, philo2;
// 	if (pthread_mutex_init(&lock, NULL) != 0)
// 		perror(" ");
// 	pthread_create(&philo1, NULL, fun, NULL);
// 	pthread_create(&philo2, NULL, fun, NULL);
// 	pthread_join(philo1, NULL);
// 	pthread_join(philo2, NULL);
// 	return (0);
// }

/*_________recurcive lock___________*/ //! Prb
// pthread_mutex_t lock;

// int fun(int i)
// {
// 	if (i == 1)
// 	{
// 		pthread_mutex_lock(&lock);
// 		write(1, "nothing\n", 8);
// 		pthread_mutex_unlock(&lock);
// 		return (9);
// 	}
// 	pthread_mutex_init(&lock, NULL);
// 	pthread_mutex_lock(&lock);
// 	fun(i + 1);
// 	pthread_mutex_unlock(&lock);
// 	// pthread_mutex_destroy(&lock);
// }

// int main()
//* {
//* 	int i = 0;
//* 	fun(i);
//* }

// /*______simple______*/

// void *fun(void *ptr)
// {
// 	printf("hello from thead\n");
// 	return (NULL);
// }

// int main()
// {
// 	pthread_t  id_1;

// 	pthread_create(&id_1 , NULL,fun, NULL);
// 	pthread_join(id_1, NULL);
// }

/*_______integert_manipulation_thread________*/
// amm i learn
// pthread_mutex_t lock;
// void *init_integer(void *ptr_int)
// {
// 	int *integer = (int *)ptr_int;
// 	pthread_mutex_lock(&lock);
// 	*integer = 42;
// 	pthread_mutex_unlock(&lock);
// 	return (NULL);
// }

// void	*print_integer(void *ptr_integer)
// {
// 	if (*(int *)ptr_integer == 42)
// 		printf("the int is\n");

// 	return (NULL);
// }

// int main()
// {
// 	pthread_t id , id_1;
// 	int integer = 11;
// 	pthread_create(&id, NULL, init_integer, &integer);
// 	pthread_create(&id_1, NULL, print_integer, &integer);
// 	pthread_join(id, NULL);
// 	pthread_join(id_1, NULL);

// }

/*________fix_the_data_race_______*/
// pthread_mutex_t lock;
// int counter = 0;
// // AFTER INIT THE LOCK WE WILL USE IT THERE
// void *increment(void *arg) {
//     for (int i = 0; i < 1000; i++)
// 	{
// 		pthread_mutex_lock(&lock);
// 		counter++;
// 		pthread_mutex_unlock(&lock);
// 	}
//     return (NULL);
// }

/*______this is consider race condition______--*/
// int main()
// {
// 	int id = fork();

// 	if (id == 0)
// 	{
// 		printf("c");
// 		return (0);
// 	}
// 	printf("p");
// }

/*_____example of sleep holding the lock____*/
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// void *worker(void *arg) {
//     sleep(1);
//     printf("home\n");                  //  Sleeps while holding the lock!
//     pthread_mutex_lock(&lock);  //  Locks the mutex
//     pthread_mutex_unlock(&lock);
//     return (NULL);
// }

// int main() {
//     pthread_t t1, t2;
//     pthread_create(&t1, NULL, worker, NULL);
//     pthread_create(&t2, NULL, worker, NULL);
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     return (0);
// }

/*__get_next_id__*/

// pthread_mutex_t lock;

// void    *get_next_id(void *ptr)
// {
//     static long id = 1;

//     // pthread_mutex_lock(&lock);
//     id++;
//     printf("thread number : %ld\n", id);
//     // pthread_mutex_unlock(&lock);
// }

//  int main()
//  {
//     pthread_t id, id1;
//     pthread_mutex_init(&lock, NULL);
//     pthread_create(&id, NULL, get_next_id, NULL);
//     pthread_create(&id1, NULL, get_next_id, NULL);
//     pthread_join(id, NULL);
//     pthread_join(id1, NULL);
//  }

///?____ Detached threads and resource cleanup_____---*/
// #include <fcntl.h>

// void    *exit_andbyebye(void *ptr)
// {
//     int fd = open("output.log", O_CREAT | O_RDWR, 0777);
//     write(1 ,"Detached thread exits\n", 22);
//     close(fd);
// }

//  int main()
//  {
//     pthread_t id;
//     pthread_create(&id, NULL, exit_andbyebye, NULL);
//     pthread_detach(id);
//  }

// void *thread1(void *arg) {
//     pthread_mutex_lock(&m1);
//     pthread_mutex_unlock(&m1);
//     pthread_mutex_lock(&m2);
//     pthread_mutex_unlock(&m2); // Deadlock here
//     /* ... */
// }

// void *thread2(void *arg) {
//     pthread_mutex_lock(&m2);
//     pthread_mutex_unlock(&m2);
//     pthread_mutex_lock(&m1);
//     pthread_mutex_unlock(&m1); // Deadlock here // Deadlock here
//     /* ... */
// }
