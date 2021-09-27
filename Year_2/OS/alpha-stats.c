#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
al(int sh_char, int sh_stats, int id_sem)
{
    char* ch;
    long* stats;
    int index;

    if ((ch = (char*)shmat(sh_char, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    if ((stats = (long*)shmat(sh_stats, NULL, 0)) == (long*)-1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        WAIT(id_sem, 1);
        if (strcmp(ch, "exit") == 0) {
            break;
        }

        if (*ch >= 'A' && *ch <= 'Z')
            *ch = *ch + 32;

        index = *ch - 97;
        stats[index]++;

        SIGNAL(id_sem, 0);
    }
}

void
mz(int sh_char, int sh_stats, int id_sem)
{
    char* ch;
    long* stats;
    int index;

    if ((ch = (char*)shmat(sh_char, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    if ((stats = (long*)shmat(sh_stats, NULL, 0)) == (long*)-1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        WAIT(id_sem, 2);
        if (strcmp(ch, "exit") == 0) {
            break;
        }

        if (*ch >= 'A' && *ch <= 'Z')
            *ch = *ch + 32;

        index = *ch - 97;
        stats[index]++;

        SIGNAL(id_sem, 0);
    }
}

int
main(int argc, char* argv[])
{
    int fd;
    struct stat sb;
    char* addr;
    int sh_char, sh_stats; /* segments CHAR and STATS */
    long* msg_stats;
    char* ch;
    pid_t p_al, p_mz;
    int id_sem;
    int i;
    int skip_wait_p;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.txt>", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    fstat(fd, &sb);

    if ((addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    if ((sh_char = shmget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((sh_stats = shmget(IPC_PRIVATE, sizeof(long) * 26, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("shmget");
        exit(1);
    }

    /* Set to 0 every stats element */
    if ((msg_stats = (long*)shmat(sh_stats, NULL, 0)) == (long*)-1) {
        perror("shmat");
        exit(1);
    }

    for (i = 0; i < 26; ++i)
        *(msg_stats + i) = 0;

    /* Create 3 semaphores */
    if ((id_sem = semget(IPC_PRIVATE, 3, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        perror("semget");
        exit(1);
    }

    semctl(id_sem, 0, SETVAL, 1);
    semctl(id_sem, 1, SETVAL, 0);
    semctl(id_sem, 2, SETVAL, 0);

    p_al = fork();
    if (p_al == -1) {
        perror("fork");
        exit(1);
    }

    if (p_al == 0) {
        al(sh_char, sh_stats, id_sem);
        exit(0);
    }

    p_mz = fork();
    if (p_mz == -1) {
        perror("fork");
        exit(1);
    }

    if (p_mz == 0) {
        mz(sh_char, sh_stats, id_sem);
        exit(0);
    }

    if ((ch = (char*)shmat(sh_char, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    skip_wait_p = 0;
    for (i = 0; i < sb.st_size; ++i) {
        if (!skip_wait_p)
            WAIT(id_sem, 0);

        strcpy(ch, addr + i);

        skip_wait_p = 0;
        if ((*ch >= 'a' && *ch <= 'l') || (*ch >= 'A' && *ch <= 'L')) {
            SIGNAL(id_sem, 1);
        } else if ((*ch >= 'm' && *ch <= 'z') || (*ch >= 'M' && *ch <= 'Z')) {
            SIGNAL(id_sem, 2);
        } else {
            skip_wait_p = 1;
        }
    }

    strcpy(ch, "exit");
    SIGNAL(id_sem, 1);
    SIGNAL(id_sem, 2);

    wait(NULL);
    wait(NULL);

    for (i = 0; i < 26; ++i)
        printf("%c = %ld\n", i + 97, msg_stats[i]);

    shmctl(sh_char, IPC_RMID, NULL);
    shmctl(sh_stats, IPC_RMID, NULL);
    semctl(id_sem, 3, IPC_RMID);
    munmap(addr, sb.st_size);

    return 0;
}
