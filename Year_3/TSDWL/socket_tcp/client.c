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
    char buffer[1024];
    int nbytes;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error with socket creation");
        exit(1);
    }

    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) == -1) {
        perror("Can't convert IP in bytes");
        exit(1);
    }

    addrlen = sizeof(addr);

    if ((connect(sockfd, (struct sockaddr*)&addr, addrlen)) == -1) {
        perror("Error with the connection");
        exit(1);
    }

    nbytes = 0;
    do {
        if (strncmp(buffer, "quit", 4) == 0)
            break;

        if (nbytes == -1) {
            perror("Error sending data");
            break;
        }

        fgets(buffer, 1024, stdin);

    } while ((nbytes = send(sockfd, buffer, strlen(buffer), 0)) > 0);

    if (recv(sockfd, buffer, 1024, 0) > 0) {
        printf("%s", buffer);
    }

    close(sockfd);

    return 0;
}
