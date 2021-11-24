#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

#define PORT 3233

void
ban(char* ban_list[], char* address, int* index, int *ban_size)
{
    if (*index > 4) {
        *index = 0;
    }

    if (*ban_size < 5) (*ban_size)++;

    strcpy(ban_list[*index], address);

    (*index)++;
}

int
is_banned_addr(char* ban_list[], int n, char* address)
{
    int i;

    for (i = 0; i < n; ++i) {
        if (strcmp(ban_list[i], address) == 0)
            return 1;
    }

    return 0;
}

int
main(int argc, char* argv[])
{
    int sockfd, clientfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    char buffer[12];
    int nbytes;
    char last_not_valid[15];
    time_t now_time;
    struct tm* now;
    char* addr_str;
    int i;
    int ban_i;
    int ban_size;
    char* ban_list[5];

    for (i = 0; i < 5; ++i) {
        ban_list[i] = malloc(sizeof(char) * 15);
    }

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1])); // TODO: change with PORT
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

    ban_i = ban_size = 0;
    while (1) {
        if ((clientfd = accept(sockfd, (struct sockaddr*)&addr, &addrlen)) == -1) {
            perror("accept");
            continue;
        }

        if ((nbytes = read(clientfd, buffer, sizeof(buffer))) == -1) {
            perror("read");
            goto clientclear;
        }

        buffer[nbytes-1] = 0;
        addr_str = inet_ntoa(addr.sin_addr);

        if (is_banned_addr(ban_list, ban_size, addr_str)) {
            sprintf(buffer, "BANNED\n");
        } else if (strncmp(buffer, "TIME", 4) == 0) {
            time(&now_time);
            now = gmtime(&now_time);
            sprintf(buffer, "%d:%d:%d UTC\n", now->tm_hour, now->tm_min, now->tm_sec);
            memset(last_not_valid, 15, 0);
        } else {
            sprintf(buffer, "N/A\n");
            if (strcmp(last_not_valid, addr_str) == 0) {
                ban(ban_list, addr_str, &ban_i, &ban_size);
                sprintf(buffer, "BANNED\n");
            } else {
                strcpy(last_not_valid, addr_str);
            }
        }
        write(clientfd, buffer, strlen(buffer));

clientclear:
        close(clientfd);
    }

    for (i = 0; i < 5; ++i) {
        free(ban_list[i]);
    }

    close(sockfd);
    return 0;
}
