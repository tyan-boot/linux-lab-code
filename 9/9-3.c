#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


static sem_t full, empty;
static pthread_mutex_t mutex;

#define BUFFERSIZE 5

struct msgbuf
{
    pid_t id;
    time_t mytime;
};

static struct msgbuf msg[BUFFERSIZE];
static int in = 0, out = 0;

void *producer(void *arg)
{
    int i;
    time_t rt;

    for (i = 1; i <= 10; ++i)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        msg[i].id = pthread_self();
        time(&msg[i].mytime);

        printf("生产者 %d 第 %d 次写消息, id = %u, time = %s\n", arg, i, msg[in].id, ctime(&msg[in].mytime));

        in = ++in % 5;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        srand(time(&rt));
        sleep(rand() % 5);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int i;
    time_t rt;

    for (i = 1; i <= 10; ++i)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        printf("消费者 %d 第 %d 次读消息， id = %u, time = %s\n", arg, i, msg[out].id, ctime(&msg[out].mytime));

        out = ++out % 5;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        srand(time(&rt));
        sleep(3 + rand() % 5);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t pid1, pid2;
    pthread_t cid1, cid2;

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 5);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&pid1, NULL, producer, 1);
    pthread_create(&pid2, NULL, producer, 2);

    pthread_create(&cid1, NULL, consumer, 1);
    pthread_create(&cid2, NULL, consumer, 2);


    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    pthread_join(cid1, NULL);
    pthread_join(cid2, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}