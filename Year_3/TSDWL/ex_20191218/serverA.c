#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void
print_buffer_digits(char* buffer, int n)
{
    char* ch = buffer;
    int i;

    for (i = 0; i < n && isdigit(*ch); ++i, ch++) {
        printf("%c", *ch);
    }
    printf("\n");
}

int
main(int argc, char* argv[])
{
    int sockfd, clientfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    char buffer[1024];
    int nbytes, ntotbytes;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = INADDR_ANY;
    addrlen = sizeof(addr);

    if (bind(sockfd, (struct sockaddr*)&addr, addrlen) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 1) == -1) {
        perror("listen");
        exit(1);
    }

    while (1) {
        if ((clientfd = accept(sockfd, (struct sockaddr*)&addr, &addrlen)) == -1) {
            perror("accept");
            continue;
        }

        ntotbytes = 0;

        while ((nbytes = read(clientfd, buffer, sizeof(buffer) - ntotbytes)) != 0) {
            if (nbytes == -1) {
                perror("error reading");
                goto closeclient;
            }
            ntotbytes += nbytes;
        }

        print_buffer_digits(buffer, ntotbytes);

    closeclient:
        close(clientfd);
    }

    close(sockfd);
    return 0;
}
