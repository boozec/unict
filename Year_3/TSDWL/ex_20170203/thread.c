#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int n;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void*
fnO(void* arg)
{
    int xrand;
    int count = 0;

    while (1) {
        usleep(200 * 1000);
        do {
            xrand = rand();
        } while ((xrand % 2) == 1);

        count++;
        pthread_mutex_lock(&mutex);
        printf("Thread O, count = %d, old x = %d, x = %d, even = %d\n", count, n, n+xrand, ((n+xrand) % 2)==0);
        n += xrand;

        if ((count == 1000) || (count >= 10 && (n%2) == 0)) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

    }

    printf("Thread O terminated.\n");
    pthread_exit(NULL);
}

void*
fnE(void* arg)
{
    int xrand;
    int count = 0;

    while (1) {
        usleep(200 * 1000);
        do {
            xrand = rand();
        } while ((xrand % 2) == 0);

        count++;
        pthread_mutex_lock(&mutex);
        printf("\tThread E, count = %d, old x = %d, x = %d, odd = %d\n", count, n, n+xrand, ((n+xrand) % 2)==1);
        n += xrand;

        if ((count == 1000) || (count >= 10 && (n%2) == 1)) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }

    printf("\tThread E terminated.\n");
    pthread_exit(NULL);
}

int
main()
{
    pthread_t tO, tE;
    srand(time(NULL));
    n = 0;

    pthread_create(&tO, NULL, &fnO, NULL);
    pthread_create(&tE, NULL, &fnE, NULL);

    pthread_join(tO, NULL);
    pthread_join(tE, NULL);

    return 0;
}
