/*
    Homework n.1

    Scrivere un programma in linguaggio C che permetta di copiare un numero
    arbitrario di file regolari su una directory di destinazione preesistente.

    Il programma dovra' accettare una sintassi del tipo:
     $ homework-1 file1.txt path/file2.txt "nome con spazi.pdf" directory-destinazione
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int copyfile(int*, int*);

int main(int argc, char* argv[0])
{
    int fd, fd_dst;
    int i;
    unsigned long size;
    char dst[1024];
    char buffer[1024];
    char *p1, *p2;

    if (argc < 3) {
        fprintf(stderr, "Use %s <src1> [<src2>..] <dst>", argv[0]);
        exit(1);
    }

    i = 1;
    strncpy(dst, argv[argc - 1], 1024);
    size = strlen(dst);
    strncpy(dst + size, "/", 1024 - size);
    size++;
    while (i < argc - 1) {
        /* Open the source file */
        if ((fd = open(argv[i], O_RDONLY)) == -1) {
            perror(argv[i]);
            exit(1);
        }

        /* Open the destination file */
        strncpy(buffer, dst, size);
        p1 = p2 = argv[i++];
        while (*p2 != '\0') {
            if (*p2 == '/')
                p1 = p2 + 1;
            p2++;
        }
        strncpy(buffer + size, p1, 1024 - size);

        if ((fd_dst = open(buffer, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1) {
            perror(argv[argc - 1]);
            exit(1);
        }

        /* Ignore the return value, the last number of bytes returned. Result is
         * always = 0 */
        copyfile(&fd, &fd_dst);
        close(fd);
        close(fd_dst);
        printf("`%s` written successfully\n", buffer);
    }

    return 0;
}

int copyfile(int* src, int* dst)
{
    int n;
    char* buffer[1024];

    do {
        if ((n = read(*src, buffer, 1024)) == -1) {
            perror("Error reading the source file");
            exit(1);
        }

        if (write(*dst, buffer, n) == -1) {
            perror("Error writing the destination file");
            exit(1);
        }
    } while (n > 0);

    return n;
}
