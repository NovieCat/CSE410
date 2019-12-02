#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

//////////////////////////////////////////////////////////////////////////
//
//	Thread&MutexSample.cpp
//
//	Demonstrate use of threads and mutexes
//
//	Remember: A mutex is a binary semaphore
//
//////////////////////////////////////////////////////////////////////////

// give the threads something to do
void* doSomething(void *arg)
{
    pthread_mutex_lock(&lock);					// entering critical region, only one thread can access this at a time

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFFFFF);i++);				// work, such as it is

    printf("\n Job %d finished\n", counter);

    pthread_mutex_unlock(&lock);				// let somebody else in the critical region

	// calling return here is equivalent to calling pthread_exit() 
    return NULL;
}




int main(void)
{
    int i = 0;
    int err;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomething, NULL);	// create a new thread, that will execute "doSomething"
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

	// wait for both threads to finish
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}