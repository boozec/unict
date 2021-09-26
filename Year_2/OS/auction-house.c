#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

int
WAIT(int id_sem, int n)
{
    struct sembuf sops[1] = { { n, -1, 0 } };
    return semop(id_sem, sops, 1);
}

int
SIGNAL(int id_sem, int n)
{
    struct sembuf sops[1] = { { n, 1, 0 } };
    return semop(id_sem, sops, 1);
}

void
judge(int id_sem, int id_shm, char* auctionfile, int n_bidders)
{
    FILE* f;
    char buffer[1024];
    char ch;
    int i;
    int counter;
    char* token;
    char ob_de[1024];
    int off_min;
    int off_max;
    char* msg;
    int value;
    int bid;

    int rel_valid;
    int rel_max;
    int rel_winner;

    int abs_valid;
    int total;

    rel_valid = abs_valid = total = 0;

    if ((f = fopen(auctionfile, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    i = 0;
    counter = 1;
    while ((ch = fgetc(f)) != EOF) {
        buffer[i++] = ch;
        if (ch == '\n') {
            rel_valid = 0;
            rel_max = rel_winner = -1;
            buffer[i - 1] = '\0';

            /* Parse the string */
            token = strtok(buffer, ",");
            strcpy(ob_de, token);

            token = strtok(NULL, ",");
            off_min = atoi(token);

            token = strtok(NULL, ",");
            off_max = atoi(token);

            WAIT(id_sem, 0);
            sprintf(msg, "%s,%d,%d,%d", ob_de, counter, off_min, off_max);
            printf("J: lancio asta n.%d per %s con offerta minima di %d EUR e massima di %d EUR\n",
                counter, ob_de, off_min, off_max);
            SIGNAL(id_sem, 1);
            for (i = 0; i < n_bidders; ++i) {
                WAIT(id_sem, 0);
                strcpy(buffer, msg);
                strtok(buffer, ","); // ob_de
                strtok(NULL, ","); // counter
                off_min = atoi(strtok(NULL, ","));
                off_max = atoi(strtok(NULL, ","));
                bid = atoi(strtok(NULL, ","));
                value = atoi(strtok(NULL, ","));
                printf("J: ricevuta offerta da B%d\n", bid);

                if (value >= off_min && value <= off_max) {
                    if (value > rel_max) {
                        rel_max = value;
                        rel_winner = bid;
                    }

                    rel_valid++;
                }

                if (i == n_bidders - 1)
                    strcpy(msg, "skip");
                SIGNAL(id_sem, 1);
            }

            if (rel_winner != -1) {
                printf("J: l'asta n.%d per %s si è conclusa con %d offerte valide su %d; il vincitore è B%d che si aggiudica l'oggetto per %d EUR\n",
                    counter, ob_de, rel_valid, n_bidders, rel_winner, rel_max);
                total += rel_max;
                abs_valid++;
            } else {
                printf("J: l'asta n.%d per %s si è conclusa senza alcuna offerta valida pertanto l'oggetto non risulta assegnato\n",
                    counter, ob_de);
            }

            counter++;

            i = 0;

            printf("\n");
        }
    }

    WAIT(id_sem, 0);
    strncpy(msg, "", 2);
    semctl(id_sem, 1, SETVAL, n_bidders);

    counter--;
    printf("J: sono state svolte %d aste di cui %d andate assegnate e %d andate a vuoto; il totale raccolto è di %d EUR\n",
        counter, abs_valid, (counter - abs_valid), total);

    fclose(f);
}

void
bidder(int id_sem, int id_shm, int i, int n)
{
    char* msg;
    char ob_de[1024];
    char* token;
    int off_min, off_max, counter;
    int value;
    char buffer[1024];

    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        WAIT(id_sem, 1);
        if (strcmp(msg, "") == 0) {
            break;
        }
        if (strcmp(msg, "skip") != 0) {
            /* Parse the string */
            strcpy(buffer, msg);
            token = strtok(buffer, ",");
            strcpy(ob_de, token);

            token = strtok(NULL, ",");
            counter = atoi(token);

            token = strtok(NULL, ",");
            off_min = atoi(token);

            token = strtok(NULL, ",");
            off_max = atoi(token);

            value = rand() % off_max;

            printf("B%d: invio offerta di %d EUR per asta n.%d\n", i, value, counter);
            sprintf(msg, "%s,%d,%d,%d,%d,%d", ob_de, counter, off_min, off_max, i, value);
        }
        SIGNAL(id_sem, 0);
    }
}

int
main(int argc, char* argv[])
{
    int id_sem;
    int id_shm;
    pid_t pid_judge;
    int n;
    pid_t* pid_bidders;
    int i;

    srand(time(NULL));
    n = atoi(argv[2]);
    if (n < 1) {
        fprintf(stderr, "<num-bidders> must be greater than 0\n");
        exit(1);
    }

    pid_bidders = malloc(sizeof(pid_t) * n);

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <auction-file> <num-bidders>", argv[0]);
        exit(1);
    }

    if ((id_shm = shmget(IPC_PRIVATE, 2048, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((id_sem = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("semget");
        exit(1);
    }

    semctl(id_sem, 0, SETVAL, 1);
    semctl(id_sem, 1, SETVAL, 0);

    pid_judge = fork();
    if (pid_judge == -1) {
        perror("fork");
        exit(1);
    }

    if (pid_judge == 0) {
        judge(id_sem, id_shm, argv[1], n);
        exit(0);
    }

    for (i = 0; i < n; ++i) {
        pid_bidders[i] = fork();
        if (pid_bidders[i] == -1) {
            perror("fork");
            exit(1);
        }

        if (pid_bidders[i] == 0) {
            bidder(id_sem, id_shm, i + 1, n);
            exit(0);
        }
    }

    for (i = 0; i <= n; ++i)
        wait(NULL); // n+1, where 1 is `judge`

    if (shmctl(id_shm, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    if (semctl(id_sem, 2, IPC_RMID) == -1) {
        perror("semctl");
        exit(1);
    }

    free(pid_bidders);
    return 0;
}
