#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>


#define MAX 10

static pthread_t pthread[2];
static pthread_mutex_t mutex;

static int number = 0, i;

void *thread1(void *arg)
{
    printf("[Thread 1]: I'm thread 1\n");

    for (i = 0; i < MAX; ++i)
    {
        printf("[Thread 1]: number = %d\n", number);

        pthread_mutex_lock(&mutex);
        number++;
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }

    printf("[Thread 1]: Main waiting?\n");
    pthread_exit(NULL);
}

void *thread2(void *arg)
{
    printf("[Thread 2]: I'm thread 2\n");

    for (i = 0; i < MAX; ++i)
    {
        printf("[Thread ]: number = %d\n", number);

        pthread_mutex_lock(&mutex);
        number++;
        pthread_mutex_unlock(&mutex);

        sleep(3);
    }

    printf("[Thread 2]: Main waiting?\n");
    pthread_exit(NULL);

}

void thread_create()
{
    int temp;

    memset(&pthread, 0, sizeof(pthread));

    if ((temp = pthread_create(&pthread[0], NULL, thread1, NULL)) != 0)
        printf("Create thread 1 failed\n");
    else
        printf("Thread 1 created\n");

    if ((temp = pthread_create(&pthread[1], NULL, thread2, NULL)) != 0)
        printf("Create thread 2 failed\n");
    else
        printf("Thread 2 created\n");
}

void thread_wait()
{
    if (pthread[0] != 0)
    {
        pthread_join(pthread[0], NULL);
        printf("Thread 1 stopped\n");
    }

    if (pthread[1] != 0)
    {
        pthread_join(pthread[1], NULL);
        printf("Thread 2 stopped\n");
    }
}

int main()
{
    pthread_mutex_init(&mutex, NULL);

    printf("[Thread Main]: Creating threads\n");
    thread_create();

    printf("[Thread Main]: Waiting child threads\n");
    thread_wait();

    return 0;
}