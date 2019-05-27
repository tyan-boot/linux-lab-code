#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct node
{
    int n_number;
    struct node *n_next;
} node;

static struct node *head = NULL;

static void cleanup_handler(void *arg)
{
    printf("Clean up handler of second thread\n");
    free(arg);

    pthread_mutex_unlock(&mutex);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

static void *thread_func(void *arg)
{
    struct node *p = NULL;

    pthread_cleanup_push(cleanup_handler, p)

            pthread_mutex_lock(&mutex);

            while (1)
            {
                while (head == NULL)
                {
                    pthread_cond_wait(&cond, &mutex);
                }

                p = head;
                head = head->n_next;

                printf("God %d from front of queue\n", p->n_number);

                free(p);
            }

    pthread_cleanup_pop(0);
}

#pragma clang diagnostic pop

int main()
{
    pthread_t pthread;
    int i;

    struct node *p;

    pthread_create(&pthread, NULL, thread_func, NULL);

    for (i = 0; i < 10; i++)
    {
        p = (struct node *) malloc(sizeof(struct node));
        p->n_number = i;

        pthread_mutex_lock(&mutex);
        p->n_next = head;
        head = p;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    pthread_cancel(pthread);
    pthread_join(pthread, NULL);

    return 0;
}