/*
    Homework n.8

    Modificare l'homework precedente (n.7) sostituendo il canale di comuniciazione
    offerto dalla coda di messaggi tra padre e figlio con un segmento di memoria
    condiviso e una coppia di semafori (esattamente due) opportunamente utilizzati
    per il coordinamento.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DIM_MSG 1024

int
WAIT(int des, int n)
{
    struct sembuf op[1] = { { n, -1, 0 } };
    return semop(des, op, 1);
}

int
SIGNAL(int des, int n)
{
    struct sembuf op[1] = { { n, 1, 0 } };
    return semop(des, op, 1);
}

void
execute(int id_shm, int id_sem)
{
    pid_t pid;
    char* msg;
    char command[DIM_MSG];
    int n;
    char* p;
    int pipefd[2];

    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        WAIT(id_sem, 0);

        /* The variable `command` will be the substring of the passed string
         * until the first space, ignoring all parameters */
        n = 0;
        p = msg;
        while (*p != '\0') {
            if (*p == ' ')
                break;
            n++;
            p++;
        }

        strncpy(command, msg, n);
        command[n] = '\0';

        if (strcmp(command, "exit") == 0)
            break;

        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(1);
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            dup2(pipefd[1], 1);
            dup2(pipefd[1], 2);
            close(pipefd[0]);
            execlp(command, "", NULL);
            fprintf(stderr, "Error executing '%s'\n", command);
            exit(1);
        } else {
            wait(NULL);

            close(pipefd[1]);
            n = read(pipefd[0], msg, 1024);
            msg[n] = '\0';
            SIGNAL(id_sem, 1);
            close(pipefd[0]);
        }
    }
}

int
main()
{
    int id_shm, id_sem;
    int pid;
    int n;
    char* msg;

    if ((id_shm = shmget(IPC_PRIVATE, DIM_MSG, IPC_CREAT | 0644)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((id_sem = semget(IPC_PRIVATE, 2, IPC_CREAT | 0644)) == -1) {
        perror("semget");
        exit(1);
    }

    /* Set values to 0 */
    semctl(id_sem, 0, SETVAL, 0);
    semctl(id_sem, 1, SETVAL, 0);

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    if (pid != 0) {
        while (1) {
            printf("Insert a command: ");
            fgets(msg, DIM_MSG, stdin);
            n = strlen(msg);
            msg[n - 1] = '\0';

            /* Ignore empty string */
            if (strcmp(msg, "") == 0)
                continue;

            SIGNAL(id_sem, 0);

            if (strcmp(msg, "exit") == 0) {
                break;
            }

            WAIT(id_sem, 1);
            printf("%s\n", msg);
            sleep(1);
        }
    } else {
        execute(id_shm, id_sem);
    }

    shmctl(id_shm, IPC_RMID, NULL);
    semctl(id_sem, 0, IPC_RMID, 0);

    return 0;
}
