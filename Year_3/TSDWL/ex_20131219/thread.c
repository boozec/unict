#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int m;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void*
fn_t1(void* arg)
{
    int xrand;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (m >= 1 && m <= 5) {
            xrand = (rand() % 10) + 1;
            printf("Thread 1: (m = %d, xrand = %d)\n", m, xrand);
            m = xrand;
            pthread_cond_signal(&cond);
        } else {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
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
            printf("\t\t\tThread 2: (m = %d, xrand = %d)\n", m, xrand);
            m = xrand;
            pthread_cond_signal(&cond);
        } else {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
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
