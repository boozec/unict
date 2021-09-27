#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 1024

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
filter(int id_shm, int id_sem, int index, int n, char* expr)
{
    char* msg;
    int quit;
    char* token;
    int action;
    char* word;
    char* j;
    char k[MAX_LEN];
    unsigned w;
    char c[1];
    char next_msg[MAX_LEN];
    char *pre_word, *next_word;

    char *token_str, *token_word;

    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    quit = 0;
    while (!quit) {
        WAIT(id_sem, index);
        if (strcmp(msg, "{{EOF}}") == 0) {
            quit = 1;
        } else {
            switch (expr[0]) {
            case '^':
                action = 0;
                break;
            case '_':
                action = 1;
                break;
            case '%':
                action = 2;
                break;
            }
            word = expr + 1;

            token = strtok_r(msg, " ", &token_str);
            next_msg[0] = '\0';
            while (token) {
                if (action == 0 || action == 1) {
                    j = strstr(token, word);
                    if (j) {
                        k[0] = '\0';
                        for (w = 0; w < strlen(word); ++w) {
                            if (action == 0)
                                c[0] = toupper(word[w]);
                            else
                                c[0] = tolower(word[w]);

                            strcat(k, c);
                        }
                        strncpy(j, k, strlen(word));
                    }
                } else {
                    strcpy(pre_word, word);
                    pre_word = strtok_r(pre_word, ",", &token_word);
                    next_word = strtok_r(NULL, ",", &token_word);

                    j = strstr(token, pre_word);
                    if (j) {
                        strcpy(j, next_word);
                    }
                }
                strcat(next_msg, token);
                strcat(next_msg, " ");

                token = strtok_r(NULL, " ", &token_str);
            }
            strcpy(msg, next_msg);
        }

        SIGNAL(id_sem, 0);
        if (index == n)
            SIGNAL(id_sem, 0);
    }
}

int
main(int argc, char* argv[])
{
    int id_shm;
    int id_sem;
    int i;
    pid_t pid;
    char buffer[MAX_LEN];
    char ch;
    FILE* f;
    char* msg;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file.txt> <filter-1> [filter-2] [...]", argv[0]);
        exit(1);
    }

    if ((f = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    if ((id_shm = shmget(IPC_PRIVATE, 1024, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((id_sem = semget(IPC_PRIVATE, argc - 1, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("semget");
        exit(1);
    }

    semctl(id_sem, 0, SETVAL, 1);

    /* Create n process for n filters */
    for (i = 0; i < argc - 2; ++i) {
        semctl(id_sem, i + 1, SETVAL, 0);
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            filter(id_shm, id_sem, i + 1, argc - 2, argv[i + 2]);
            exit(0);
        }
    }

    i = 0;
    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    while ((ch = fgetc(f)) != EOF) {
        buffer[i++] = ch;
        if (ch == '\n') {
            buffer[i - 1] = '\0';
            WAIT(id_sem, 0);
            strncpy(msg, buffer, strlen(buffer) + 1);
            for (i = 0; i < argc - 2; ++i) {
                SIGNAL(id_sem, i + 1);
                WAIT(id_sem, 0);
            }
            printf("%s\n", msg);
            i = 0;
        }
    }

    WAIT(id_sem, 0);
    strcpy(msg, "{{EOF}}");
    for (i = 0; i < argc - 2; ++i) {
        SIGNAL(id_sem, i + 1);
        WAIT(id_sem, 0);
    }

    for (i = 0; i < argc - 2; ++i)
        wait(NULL);

    shmctl(id_shm, IPC_RMID, NULL);
    semctl(id_sem, argc - 1, IPC_RMID);

    return 0;
}
