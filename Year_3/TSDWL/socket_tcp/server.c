#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 3030
#define CONNECTIONS_NUM 1

int
main(int argc, char* argv[])
{
    int sockfd, clientfd;
    struct sockaddr_in address;
    socklen_t addrlen;
    int nbytes, ntotbytes;
    char buffer[1024];

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating a new socket");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[1]));
    address.sin_addr.s_addr = INADDR_ANY;

    addrlen = sizeof(address);

    if (bind(sockfd, (struct sockaddr*)&address, addrlen) == -1) {
        perror("Error binding the port");
        exit(1);
    }

    if (listen(sockfd, CONNECTIONS_NUM) == -1) {
        perror("Can't listen that port");
        exit(1);
    }

    while (1) {
        if ((clientfd = accept(sockfd, (struct sockaddr*)&address, &addrlen)) == -1) {
            perror("Can't accept request from client");
            break;
        }

        ntotbytes = 0;
        while ((nbytes = recv(clientfd, buffer, 1024, 0)) != 0) {
            if (nbytes == -1) {
                perror("Error reading the client");
                break;
            }

            buffer[nbytes] = '\0';
            if (strncmp(buffer, "quit", 4) == 0) {
                break;
            }

            printf("%s", buffer);
            ntotbytes += nbytes;
        }

        sprintf(buffer, "Total bytes read: %d\n", ntotbytes);

        if ((nbytes = send(clientfd, buffer, strlen(buffer), 0)) != strlen(buffer)) {
            perror("Error sending back a message");
        }

        close(clientfd);
    }

    close(sockfd);

    return 0;
}
