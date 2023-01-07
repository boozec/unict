#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>

char*
check_string(char buffer[1024], int n)
{
    char* string = "yes";
    int i;

    for(i = 0; i < n; ++i) {
        if (buffer[i] != 'V' && buffer[i] != 'F') {
            strcpy(string, "no");
            break;
        }
    }

    return string;
}

int
main(int argc, char* argv[])
{
    int sockfd, clientfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    char buffer[1024];
    char* result;
    int n;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(3333);
    addr.sin_family = AF_INET;

    addrlen = sizeof(addr);

    if (bind(sockfd, (struct sockaddr*) &addr, addrlen) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 1) == -1) {
        perror("listen");
        exit(1);
    }

    while (1) {
        if ((clientfd = accept(sockfd, (struct sockaddr*) &addr, &addrlen)) == -1) {
            perror("accept");
            exit(1);
        }

        if ((n = read(clientfd, buffer, sizeof(buffer))) == -1) {
            perror("read");
            goto clientclose;
        }

        result = check_string(buffer, n);
        printf("%s\n", result);

clientclose:
        close(clientfd);
    }

    close(sockfd);
    return 0;
}
