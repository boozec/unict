#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int x;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;

void*
t1_fn(void* arg)
{
    int m;

    while (1) {
        usleep(100 * 1000);
        m = rand() % 11;

        pthread_mutex_lock(&mutex);
        printf("th1: (x=%d, m=%d):", x, m);
        if (x == -1) {
            break;
        } else if (x == m) {
            printf("RISPOSTA CORRETTA\n");
            x = -1;
            break;
        } else if (abs(x-m) > 5) {
            printf("risposta MOLTO sbagliata\n");
            pthread_mutex_unlock(&mutex);
            pthread_cond_wait(&cond, &mutex);
        } else {
            printf("risposta sbagliata\n");
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void*
t2_fn(void* arg)
{
    while (1) {
        usleep(300* 1000);
        pthread_mutex_lock(&mutex);
        printf("\tthread 2 %d\n", x);
        if (x == -1) {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

int
main()
{
    pthread_t t1, t2;
    srand(time(NULL));
    x = rand() % 11;

    pthread_create(&t1, NULL, t1_fn, NULL);
    pthread_create(&t2, NULL, t2_fn, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
