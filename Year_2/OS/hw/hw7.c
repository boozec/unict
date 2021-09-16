/*
    Homework n.7

    Modificare l'homework precedente (n.6) facendo in modo che il figlio che
    riceve il comando da eseguire tramite la coda, catturi lo standard output
    e lo standard error del figlio nipote usando la redirezione su pipe tra
    processi. L'output catturato dovrà essere mandato indietro al padre
    tramite un messaggio (per semplicita', assumiamo sufficiente grande).
    Tale contenuto sara' poi visualizzato sul terminale dal padre.

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
#define MTYPE_EXE 2

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
    int pipefd[2];

    while (1) {
        if (msgrcv(qid, (void*)&msg, 1024, MTYPE, 0) == -1) {
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
            n = read(pipefd[0], msg.mtext, 1024);
            msg.mtext[n] = '\0';
            msg.mtype = MTYPE_EXE;
            close(pipefd[0]);

            if (msgsnd(qid, (void*)&msg, strlen(msg.mtext) + 1, 0) == -1) {
                perror("msgsnd");
                exit(1);
            }
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
        while (1) {
            printf("Insert a command: ");
            fgets(msg.mtext, 1024, stdin);
            n = strlen(msg.mtext);
            msg.mtext[n - 1] = '\0';
            msg.mtype = MTYPE;

            /* Ignore empty string */
            if (strcmp(msg.mtext, "") == 0)
                continue;

            if (msgsnd(qid, (void*)&msg, sizeof(msg.mtext), IPC_NOWAIT) == -1) {
                perror("msgsnd");
                exit(1);
            }

            /* Check first if the message is exit, because executing this when
             * message is "exit" raises 
             * msgrcv: Identifier removed
             */
            if (strcmp(msg.mtext, "exit") == 0) {
                break;
            }

            if (msgrcv(qid, (void*)&msg, 1024, MTYPE_EXE, 0) == -1) {
                perror("msgrcv");
                exit(1);
            }

            printf("%s\n", msg.mtext);
            sleep(1);
        }
    } else {
        execute(qid);
    }

    return 0;
}
