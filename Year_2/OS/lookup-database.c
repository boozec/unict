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

typedef struct {
    char name[256];
    int value;
} pairs;

typedef struct {
    int n;
    long value;
} out_row;

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

pairs*
find_row(char* name, pairs* rows, int n)
{
    for (int i = 0; i < n; ++i) {
        if (strcmp(rows[i].name, name) == 0)
            return &rows[i];
    }

    return NULL;
}

void
parse_rows(FILE* f, pairs* rows)
{
    int i, ci; /* ci stands for character index */
    char* token;
    char buf[1024];
    int pi; /* pi stands for pair index */
    i = ci = 0;
    char ch;

    while ((ch = (char)fgetc(f)) != EOF) {
        if (ch != '\n') {
            buf[ci++] = ch;
        } else {
            buf[ci] = '\0';
            token = strtok(buf, ";");
            if (token == NULL) {
                goto free_and_return;
            }

            pi = 0;
            while (token != NULL) {
                if (pi == 0) {
                    strcpy(rows[i].name, token);
                } else if (pi == 1) {
                    rows[i].value = atoi(token);
                } else {
                    goto free_and_return;
                }
                pi++;
                token = strtok(NULL, ";");
            }

            ci = 0;
            i++;
        }
    }

    return;

free_and_return:
    perror("<db-file> has a bad format");
    free(rows);
    exit(1);
}

void
db(pairs* rows, char* db_path, int id_shm_db_in, int id_shm_db_out, int id_sem, int fin_n)
{
    FILE* f;
    int n; /* It represents the number of lines of the file <db-file> */
    char ch;
    char* msg;
    char* msgout;
    int count_newline;
    char* token;
    int in_n;
    pairs* row;

    if ((f = fopen(db_path, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    n = 0;
    while ((ch = (char)fgetc(f)) != EOF) {
        if (ch == '\n')
            n++;
    }

    fseek(f, 0, SEEK_SET);
    rows = malloc(sizeof(pairs) * n);
    parse_rows(f, rows);
    fclose(f);

    printf("DB: letti n. %d record da file\n", n);

    if ((msg = (char*)shmat(id_shm_db_in, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    if ((msgout = (char*)shmat(id_shm_db_out, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    count_newline = 0;
    while (count_newline < fin_n) {
        WAIT(id_sem, 0);
        if (strcmp(msg, "") == 0) {
            count_newline++;
        } else {
            token = strtok(msg, ";");
            in_n = atoi(token);
            token = strtok(NULL, ";");
            row = find_row(token, rows, n);
            if (row == NULL) {
                printf("DB: query '%s' da IN%d non trovata\n", token, in_n);
            } else {
                WAIT(id_sem, 3);
                sprintf(msgout, "%d;%s;%d", in_n, row->name, row->value);
                SIGNAL(id_sem, 2);
                printf("DB: query '%s' da IN%d trovata con valore %d\n", token, in_n, row->value);
            }
        }
        SIGNAL(id_sem, 1);
    }

    WAIT(id_sem, 3);
    strcpy(msgout, "");
    SIGNAL(id_sem, 2);
}

void
out(int id_shm_db_out, int id_sem, int fin_n)
{
    char* msg;
    out_row* processes; /* at i-index there is the data of process-i */
    char* token;
    int* n = &fin_n;
    int index;
    int i;

    processes = malloc(sizeof(out_row) * (*n));
    for (i = 0; i < *n; ++i) {
        processes[i].n = 0;
        processes[i].value = 0;
    }

    if ((msg = (char*)shmat(id_shm_db_out, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        WAIT(id_sem, 2);

        if (strcmp(msg, "") == 0)
            break;

        token = strtok(msg, ";");
        index = atoi(token);
        strtok(NULL, ";"); /* Ignore the `name` param */
        token = strtok(NULL, ";");
        processes[index - 1].n++;
        processes[index - 1].value += atol(token);

        SIGNAL(id_sem, 3);
    }

    for (i = 0; i < *n; ++i) {
        printf("OUT: ricevuti n.%d valori validi per IN%d con totale %lu\n", processes[i].n, i + 1, processes[i].value);
    }

    free(processes);
}

void
fn_in(int id_in, char* input_file, int id_shm_db_in, int id_sem)
{
    FILE* f;
    char buf[DIM_MSG];
    char ch;
    int ci;
    char* msg;
    int i;
    char id_in_str[5]; /* Max process is 99999 */

    sprintf(id_in_str, "%d", id_in);

    if ((f = fopen(input_file, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    if ((msg = (char*)shmat(id_shm_db_in, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    ci = strlen(id_in_str) + 1;
    for (i = 0; i < strlen(id_in_str); ++i) {
        buf[i] = id_in_str[i];
    }
    buf[i] = ';';

    i = 1;

    while ((ch = fgetc(f)) != EOF) {
        buf[ci++] = ch;
        if (ch == '\n') {
            buf[ci - 1] = '\0';

            WAIT(id_sem, 1);
            /* Write the `buf` into the shared memory buffer with db */
            strncpy(msg, buf, ci);

            printf("IN%d: inviata query n.%d '%s'\n", id_in, i, msg + strlen(id_in_str) + 1);

            ci = strlen(id_in_str) + 1;
            SIGNAL(id_sem, 0);
            i++;
        }
    }
    WAIT(id_sem, 1);
    strncpy(msg, "", 1);
    SIGNAL(id_sem, 0);

    fclose(f);
}

int
main(int argc, char** argv)
{
    int i;
    int id_shm_db_in;
    int id_shm_db_out;
    int id_sem;

    pid_t pid_db;
    pid_t pid_out;
    pid_t pid_in[argc - 2];

    pairs* rows;
    rows = NULL;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <db-file> <query-file-1> [<query-file-2>] .. [<query-file-n>]", argv[0]);
        exit(1);
    }

    /* Create the shared memory blocks */
    if ((id_shm_db_in = shmget(IPC_PRIVATE, DIM_MSG, IPC_CREAT | 0644)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((id_shm_db_out = shmget(IPC_PRIVATE, DIM_MSG, IPC_CREAT | 0644)) == -1) {
        perror("shmget");
        exit(1);
    }

    /* These are two semaphore used as mutexs */
    if ((id_sem = semget(IPC_PRIVATE, 4, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("semget");
        exit(1);
    }
    /* Set values to 0 */
    semctl(id_sem, 0, SETVAL, 0);
    semctl(id_sem, 1, SETVAL, 1);
    semctl(id_sem, 2, SETVAL, 0);
    semctl(id_sem, 3, SETVAL, 1);

    pid_db = fork();
    if (pid_db == -1) {
        perror("fork");
        exit(1);
    }

    if (pid_db == 0) {
        db(rows, argv[1], id_shm_db_in, id_shm_db_out, id_sem, argc - 2);
        exit(0);
    }

    pid_out = fork();
    if (pid_out == -1) {
        perror("fork");
        exit(1);
    }

    if (pid_out == 0) {
        out(id_shm_db_out, id_sem, argc - 2);
        exit(0);
    }

    for (i = 0; i < argc - 2; ++i) {
        pid_in[i] = fork();
        if (pid_in[i] == -1) {
            perror("fork");
            exit(1);
        }

        if (pid_in[i] == 0) {
            fn_in(i + 1, argv[i + 2], id_shm_db_in, id_sem);
            exit(0);
        }
    }

    for (i = 0; i < argc; ++i)
        wait(NULL);

    shmctl(id_shm_db_in, IPC_RMID, 0);
    shmctl(id_shm_db_out, IPC_RMID, 0);
    semctl(id_sem, 4, IPC_RMID);
    free(rows);

    return 0;
}
