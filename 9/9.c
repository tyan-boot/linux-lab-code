#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t mutex;
static int i = 0;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void *thread_1(void *arg)
{
    int idx;

    for (idx = 0; idx < 60; ++idx)
    {
        pthread_mutex_lock(&mutex);

        i++;
        printf("[Thread 1] i: %d\n", i);

        pthread_mutex_unlock(&mutex);

        sleep(2);
    }

    pthread_exit(NULL);
}

#pragma clang diagnostic pop

int main()
{
    pthread_t ptid;

    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("mutex init failed\n");
        return -1;
    }

    pthread_create(&ptid, NULL, thread_1, NULL);

    int idx;
    for (idx = 0; idx < 60; ++idx)
    {
        pthread_mutex_lock(&mutex);

        i--;
        printf("[Thread Main] i: %d\n", i);

        pthread_mutex_unlock(&mutex);

        sleep(3);
    }


    return 0;
}