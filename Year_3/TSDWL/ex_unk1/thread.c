#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int x = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void*
fn(void* arg)
{
    char* thread_name = (char*) arg;
    int xrand;
    long hit;

    hit = 0;
    while (1) {
        xrand = rand() % 1000;
        usleep(xrand);

        pthread_mutex_lock(&mutex);
        if (x > 500) {
            printf("I'm the thread %s with hit = '%ld' and x = '%d'\n", thread_name, hit, x);
            pthread_mutex_unlock(&mutex);
            break;
        }
        x++;
        pthread_mutex_unlock(&mutex);

        hit++;
    }

    pthread_exit((void*) hit);
}

int
main()
{
    pthread_t tA, tB;
    void *result1, *result2;
    long total;
    srand(time(NULL));

    pthread_create(&tA, NULL, &fn, (void*) "A");
    pthread_create(&tB, NULL, &fn, (void*) "B");

    pthread_join(tA, &result1);
    pthread_join(tB, &result2);

    total = (long) result1 + (long) result2;
    printf("Total = %ld + %ld = %ld'\n", (long) result1, (long) result2, total);
    return 0;
}
