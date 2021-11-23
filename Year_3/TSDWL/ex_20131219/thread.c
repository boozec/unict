#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int m;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;

void*
fn_t1(void* arg)
{
    int xrand;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (m >= 1 && m <= 5) {
            xrand = (rand() % 10) + 1;
            printf("Thread 1: (%d, %d)\n", m, xrand);
            m = xrand;
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_mutex_unlock(&mutex);
            pthread_cond_wait(&cond, &mutex);
        }
    }

    pthread_exit(NULL);
}

void*
fn_t2(void* arg)
{
    int xrand;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (m >= 6 && m <= 10) {
            xrand = (rand() % 10) + 1;
            printf("Thread 2: (%d, %d)\n", m, xrand);
            m = xrand;
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_mutex_unlock(&mutex);
            pthread_cond_wait(&cond, &mutex);
        }
    }

    pthread_exit(NULL);
}

int
main()
{
    pthread_t th[2];
    srand(time(NULL));
    m = (rand() % 10) + 1;

    pthread_create(&th[0], NULL, (void*)&fn_t1, NULL);
    pthread_create(&th[1], NULL, (void*)&fn_t2, NULL);
    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);

    return 0;
}
