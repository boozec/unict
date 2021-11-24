#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sample = 50;

void*
fn(void* arg)
{
    char* th = (char*) arg;
    int new_sample;

    char indent[3] = "";
    if (strcmp(th, "B") == 0)
        strcpy(indent, "\t");
    else if (strcmp(th, "C") == 0)
        strcpy(indent, "\t\t");

    while (1) {
        new_sample = (rand() % 81) + 10;
        pthread_mutex_lock(&mutex);

        printf("%sSono il thread %s: sample valeva %d, adesso vale %d\n", indent, th, sample, new_sample);
        if (sample != new_sample) {
            sample = new_sample;
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_mutex_unlock(&mutex);
            break;
        }

    }

    printf("%sSono il thread %s, e sto uscendo!\n", indent, th);

    pthread_exit(NULL);
}

int
main()
{
    pthread_t th[3];
    srand(time(NULL));

    pthread_create(&th[0], NULL, &fn, (void*) "A");
    pthread_create(&th[1], NULL, &fn, (void*) "B");
    pthread_create(&th[2], NULL, &fn, (void*) "C");

    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);
    pthread_join(th[2], NULL);

    printf("Il valore finale di sample e' %d\n", sample);

    return 0;
}
