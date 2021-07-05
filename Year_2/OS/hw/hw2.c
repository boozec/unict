/*
    Homework n.2

    Estendere l'esempio 'move.c' visto a lezione per supportare i 2 casi speciali:
    - spostamento cross-filesystem: individuato tale caso, il file deve essere
      spostato utilizzando la strategia "copia & cancella";
    - spostamento di un link simbolico: individuato tale caso, il link simbolico
      deve essere ricreato a destinazione con lo stesso contenuto (ovvero il percorso
      che denota l'oggetto referenziato); notate come tale spostamento potrebbe
      rendere il nuovo link simbolico non effettivamente valido.

    La sintassi da supportare e' la seguente:
     $ homework-2 <pathname sorgente> <pathname destinazione>
*/
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* Function from the homework 1 */
int copyfile(int*, int*);

int main(int argc, char** argv)
{
    struct stat src, dst;
    char buffer[1024];
    int fd_src, fd_dst;
    int size;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <src> <dst>", argv[0]);
        exit(1);
    }

    if (lstat(argv[1], &src) == -1) {
        perror("lstat");
        exit(1);
    }

    switch (src.st_mode & S_IFMT) {
    case S_IFREG:
        strncpy(buffer, argv[2], 1024);
        stat(dirname(buffer), &dst);

        /* Destination's father must be a directory */
        if (!S_ISDIR(dst.st_mode)) {
            fprintf(stderr, "Destination is not a directory");
        }

        if (dst.st_dev == src.st_dev) {
            if (link(argv[1], argv[2]) == -1) {
                perror("link");
                exit(1);
            }

        } else {
            if ((fd_src = open(argv[1], O_RDONLY)) == -1) {
                perror("Error opening source");
                exit(1);
            }

            if ((fd_dst = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, (src.st_mode & 0777))) == -1) {
                perror("Error opening destination");
                exit(1);
            }

            copyfile(&fd_src, &fd_dst);

            close(fd_src);
            close(fd_dst);
        }
        break;
    case S_IFLNK:
        if ((size = readlink(argv[1], buffer, 1024)) == -1) {
            perror("readlink");
            exit(1);
        }

        buffer[size] = '\0';
        if (symlink(buffer, argv[2]) == -1) {
            perror("symlink");
            exit(1);
        }
        break;
    default:
        fprintf(stderr, "Source file type not supported");
    }

    if (unlink(argv[1]) == -1) {
        perror("ulink");
        exit(1);
    }

    return 0;
}

int copyfile(int* src, int* dst)
{
    int n;
    char buffer[1024];

    do {
        if ((n = read(*src, buffer, 1024)) == -1) {
            perror("read");
            exit(1);
        }

        if (write(*dst, buffer, n) == -1) {
            perror("write");
            exit(1);
        }
    } while (n > 0);

    return n;
}
