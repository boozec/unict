/* An example of the work of this file is showed at [1]
 *
 * [1] https://it.wikipedia.org/wiki/Hypertext_Transfer_Protocol#Richiesta_GET_e_risposta_di_successo
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_WWW "./www"

typedef enum {
    GET,
    /* TODO: types below */
    HEAD,
    OPTIONS,
    POST,
    PUT,
    PATCH,
    DELETE
} methods;

typedef enum {
    /* Some of the HTTP versions defined at [1]
     *
     * [1] https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol#History
     */
    HTTP1, /* HTTP/1.0 */
    HTTP1_1, /* HTTP/1.1 */
    HTTP2, /* HTTP/2   */
} http_t;

typedef struct {
    methods method;
    char path[256]; /* FIXME: handle path with more than 256 chars */
    http_t http_version;
} request_t;

/* TODO: Make the parsing of headers */
void
read_headers(int* fd, char** headers, int* headers_num)
{
    char ch;
    int flag_read; /* Used to check the return value of `read` function */
    unsigned i;
    char buffer[1024];

    *headers_num = 0;

    while (1) {
        i = 0;

        buffer[0] = '\0';
        headers[*headers_num] = malloc(sizeof(char) * 1024);
        while ((flag_read = read(*fd, &ch, 1)) != 0) {
            if (flag_read == -1) {
                perror("Error reading the headers");
                exit(1);
            }

            buffer[i] = ch;
            if (ch == '\n' && (i < 1 || buffer[i - 1] == '\r')) {
                break;
            }

            i++;
        }

        buffer[i - 1] = '\0';
        if (i < 2) {
            break;
        }

        memcpy(headers[*headers_num], buffer, i);
        (*headers_num)++;
    }
}

void
get_client_ip(int fd, char* buffer)
{
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    getpeername(fd, (struct sockaddr*)&addr, &addr_size);
    strcpy(buffer, inet_ntoa(addr.sin_addr));
}

int
parse_first_line(request_t* request, char* header, size_t len)
{
    char* token;
    int i;

    i = 0;
    token = strtok(header, " ");
    do {
        switch (i) {
        case 0: {
            if (strcmp(token, "GET") == 0) {
                request->method = GET;
            } else {
                fprintf(stderr, "'%s' method not supported\n", token);
                goto parse_error;
            }
            /* TODO: Handle the other HTTP methods */
            break;
        }
        case 1: {
            strcpy(request->path, token);
            break;
        }
        case 2: {
            if (strcmp(token, "HTTP/1.0") == 0) {
                request->http_version = HTTP1;
            } else if (strcmp(token, "HTTP/1.1") == 0) {
                request->http_version = HTTP1_1;
            } else if (strcmp(token, "HTTP/2") == 0) {
                request->http_version = HTTP2;
            } else {
                fprintf(stderr, "'%s' version not supported\n", token);
                goto parse_error;
            }
            break;
        }
        /* If it comes here, it means that the header have more than 3 tokens */
        default: {
            fprintf(stderr, "Header does not have a valid syntax\n");
            goto parse_error;
        }
        }

        i++;
        token = strtok(NULL, " ");
    } while (token != NULL);

    return 0;

parse_error:
    return -1;
}

int
main(int argc, char* argv[])
{
    char* www_path;
    char** headers;
    int headers_num;
    unsigned i;
    int sockfd, clientfd;
    struct sockaddr_in address;
    char client_ip[20];
    socklen_t address_len;
    char* buffer;
    request_t request;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port> [root_path]", argv[0]);
        exit(1);
    }

    www_path = (argc >= 3) ? argv[2] : DEFAULT_WWW;

    /* Max 24 headers for now on the stack */
    headers = malloc(sizeof(char*) * 24);

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating a new socket");
        exit(1);
    }

    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[1]));
    address.sin_family = AF_INET;

    address_len = sizeof(address);

    if (bind(sockfd, (struct sockaddr*)&address, address_len) == -1) {
        perror("Error binding the socket");
        exit(1);
    }

    if (listen(sockfd, 1) == -1) {
        perror("Unable to listen");
        exit(1);
    }

    while (1) {
        if ((clientfd = accept(sockfd, (struct sockaddr*)&address, &address_len)) == -1) {
            perror("Error with client connection, maybe try again later");
            continue;
        }

        get_client_ip(clientfd, client_ip);
        printf("Connection from '%s':\n", client_ip);

        read_headers(&clientfd, headers, &headers_num);

        if (headers_num == 0) {
            buffer = "You must specify almost one header\n";
            write(clientfd, buffer, strlen(buffer) + 1);
        }

        parse_first_line(&request, headers[0], strlen(headers[0]));

        for (i = 0; i < headers_num; ++i) {
            free(headers + i);
        }
        printf("[Connection closed]\n\n");
        close(clientfd);
    }

    close(sockfd);
    return 0;
}
