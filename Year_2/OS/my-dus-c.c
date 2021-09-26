/*
 * Test the equivalent execution of this propgram with `du`:
 *
 * du --block-size=512 -s <path>
 *
 */
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

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
handle_scanner_end(int id_shm, int id_sem, int id_scanner, char* pathname)
{
    char* msg;

    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    WAIT(id_sem, 0);
    sprintf(msg, "%d;END;%s", id_scanner, pathname);
    SIGNAL(id_sem, 1);
}

void
stater(int id_shm, int id_sem, int* scanners, int scanners_n)
{
    char* msg;
    int n;
    struct stat sb;
    char* token;
    char* pathname;
    int sid;

    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    n = 0;
    while (n < scanners_n) {
        WAIT(id_sem, 1);
        /* I previously opened the file with `open` so I know I can read
             * that. So now I open that file with stat, because `msg` contains
             * the patname as string.
             * But first I have to parse the `msg` receiving the scanner id.
             */
        token = strtok(msg, ";");
        sid = atoi(token);
        pathname = strtok(NULL, ";");

        if (strcmp(pathname, "END") == 0) {
            pathname = strtok(NULL, ";");
            printf("%d\t%s\n", scanners[sid], pathname);
            n++;
        } else {
            stat(pathname, &sb);
            scanners[sid] += sb.st_blocks;
        }
        SIGNAL(id_sem, 0);
    }
}

void
scanner(int id_shm, int id_sem, int scanner_id, char* pathname)
{
    char* msg;
    struct stat sb;
    struct dirent* db;
    int fd;
    DIR* dp;
    char buffer[MAX_PATH_LEN];

    if ((msg = (char*)shmat(id_shm, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    if ((fd = open(pathname, O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    fstat(fd, &sb);

    if ((sb.st_mode & S_IFMT) == S_IFDIR) {
        if ((dp = opendir(pathname)) == NULL) {
            perror("opendir");
            exit(1);
        }

        while ((db = readdir(dp)) != NULL) {
            if ((strcmp(db->d_name, ".") == 0) || strcmp(db->d_name, "..") == 0)
                continue;
            sprintf(buffer, "%s/%s", pathname, db->d_name);
            scanner(id_shm, id_sem, scanner_id, buffer);
        }

        closedir(dp);
    }

    WAIT(id_sem, 0);
    sprintf(msg, "%d;%s", scanner_id, pathname);
    SIGNAL(id_sem, 1);
}

int
main(int argc, char* argv[])
{
    int id_shm;
    int i;
    pid_t pid;
    pid_t pid_scanners[argc - 1];
    int scanners[argc - 1];
    int id_sem;

    for (i = 0; i < argc - 1; ++i)
        scanners[i] = 0;

    if ((id_shm = shmget(IPC_PRIVATE, 1024, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((id_sem = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("semget");
        exit(1);
    }

    semctl(id_sem, 0, SETVAL, 1);
    semctl(id_sem, 1, SETVAL, 0);

    if (argc < 2) {
        exit(0);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        stater(id_shm, id_sem, scanners, argc - 1);
        exit(0);
    }

    for (i = 1; i < argc; ++i) {
        pid_scanners[i - 1] = fork();
        if (pid_scanners[i - 1] == -1) {
            perror("fork");
            exit(1);
        }

        if (pid_scanners[i - 1] == 0) {
            scanner(id_shm, id_sem, i - 1, argv[i]);
            handle_scanner_end(id_shm, id_sem, i - 1, argv[i]);
            exit(0);
        }
    }

    for (i = 0; i < argc; ++i)
        wait(NULL);

    if (shmctl(id_shm, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    if (semctl(id_sem, 2, IPC_RMID) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}
