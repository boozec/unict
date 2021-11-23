#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

char* V[10];

int
main()
{
    int sockfd, clientfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    int n;
    char buffer[256];
    int vi;
    int i;
    int is_present;
    int x_rand;

    srand(time(NULL));

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(7777);

    addrlen = sizeof(addr);
    if (bind(sockfd, (struct sockaddr*) &addr, addrlen) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 1) == -1) {
        perror("listen");
        exit(1);
    }

    for (i = 0; i < 10; ++i) {
        V[i] = malloc(sizeof(char) * 255);
    }
    vi = 0;

    while (1) {
        if ((clientfd = accept(sockfd, (struct sockaddr*) &addr, &addrlen)) == -1) {
            perror("accept");
            continue;
        }

        if ((n = read(clientfd, buffer, sizeof(buffer))) == -1) {
            perror("read");
            goto client_close;
        }

        buffer[n-1] = 0;
        if (strncmp(buffer, "LIST", 4) == 0) {
            for (i = 0; i < vi; ++i)
                printf("%s\n", V[i]);
        } else {
            is_present = 0;
            for (i = 0; i < vi; ++i) {
                if (strcmp(buffer, V[i]) == 0) {
                    is_present = 1;
                    printf("presente\n");
                }
            }

            if (!is_present) {
                if (vi == 9) {
                    x_rand = rand() % 10;
                    strcpy(V[x_rand], buffer);
                } else {
                    strcpy(V[vi++], buffer);
                }
                printf("inserita\n");
            }
        }
client_close:
        close(clientfd);
    }

    for (i = 0; i < 10; ++i) {
        free(V[i]);
    }

    close(sockfd);
    return 0;
}
