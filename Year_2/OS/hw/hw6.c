/*
    Homework n.6

    Scrivere un programma che crei un processo figlio con cui scambiera' dati
    tramite una coda di messaggi. Tale coda sara' creata dal padre e distrutta,
    a fine lavori, dal figlio.

    Il processo padre dovra' accettare comandi inseriti da tastiera (per semplicita'
    senza parametri) e questi dovranno essere inviati al figlio che li eseguira'
    di volta in volta creando dei processi nipoti: uno per ogni comando.

    Il tutto si dovra' arrestare correttamente all'inserimento del comando
    'exit' sul padre.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MTYPE 1

struct msgbuf {
    long mtype;
    char mtext[1024];
};

void
execute(int qid)
{
    pid_t pid;
    struct msgbuf msg;
    char command[1024];
    int n;
    char* p;

    while (1) {
        if (msgrcv(qid, (void*)&msg, sizeof(msg.mtext), MTYPE, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        /* The variable `command` will be the substring of the passed string
         * until the first space, ignoring all parameters */
        n = 0;
        p = msg.mtext;
        while (*p != '\0') {
            if (*p == ' ')
                break;
            n++;
            p++;
        }

        strncpy(command, msg.mtext, n);
        command[n] = '\0';

        if (strcmp(command, "exit") == 0)
            break;

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            execlp(command, "", NULL);
            fprintf(stderr, "Error executing '%s'\n", command);
        } else {
            wait(NULL);
        }
    }

    msgctl(qid, IPC_RMID, NULL);
}

int
main()
{
    pid_t pid;
    int qid;
    int n;

    if ((qid = msgget(IPC_PRIVATE, IPC_CREAT | 0644)) == -1) {
        perror("msgget");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid != 0) {
        struct msgbuf msg;
        msg.mtype = MTYPE;
        do {
            printf("Insert a command: ");
            fgets(msg.mtext, 1024, stdin);
            n = strlen(msg.mtext);
            msg.mtext[n - 1] = '\0';

            /* Ignore empty string */
            if (strcmp(msg.mtext, "") == 0)
                continue;

            if (msgsnd(qid, (void*)&msg, sizeof(msg.mtext), IPC_NOWAIT) == -1) {
                perror("msgsnd");
                exit(1);
            }
            sleep(1);
        } while (strcmp(msg.mtext, "exit") != 0);
    } else {
        execute(qid);
    }

    return 0;
}
