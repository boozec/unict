#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    char buffer[1024];
    int nbytes;

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Error creating a new socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;
    addrlen = sizeof(addr);

    if (bind(sockfd, (struct sockaddr*)&addr, addrlen) == -1) {
        perror("Can't bind this socket");
        exit(1);
    }

    while ((nbytes = recv(sockfd, buffer, 1024, 0)) != 0) {
        if (nbytes == -1) {
            perror("Error receiving data");
        }
        buffer[nbytes] = '\0';

        printf("%s\n", buffer);
    }

    close(sockfd);
    return 0;
}
