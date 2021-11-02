#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addrlen;

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Error with socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) == -1) {
        perror("Can't convert IP in bytes");
        exit(1);
    }
    addrlen = sizeof(addr);

    if (sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr*)&addr, addrlen) == -1) {
        perror("Message not sent");
    }

    close(sockfd);

    return 0;
}
