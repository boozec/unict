/* An example of the work of this file is showed at [1]
 *
 * [1] https://it.wikipedia.org/wiki/Hypertext_Transfer_Protocol#Richiesta_GET_e_risposta_di_successo
 */
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
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

typedef enum {
    /* Get some responses names from [1]
     *
     * [1] https://www.django-rest-framework.org/api-guide/status-codes/#successful-2xx
     */
    HTTP_200_OK,
    HTTP_206_PARTIAL_CONTENT,
    HTTP_404_NOT_FOUND,
    /* TODO: Include more and more responses */
} response_t;

char*
response_text(response_t response)
{
    char* map[] = { "200 OK", "206 PARTIAL CONTENT", "404 NOT FOUND" };

    return map[response];
}

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

    while (*headers_num < 24) {
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
parse_first_line(request_t* request, const char* header, size_t len)
{
    char* token;
    char line[255];
    int i;

    i = 0;
    strcpy(line, header);
    token = strtok(line, " ");
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
            if (token[0] != '/') {
                fprintf(stderr, "'%s' must starts with a '/'\n", token);
                goto parse_error;
            }
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

void
read_file(char* root, request_t* request, int client)
{
    /* FIXME: In Linux the max name length is 255, but here we include the 
     * root, and I don't want to use an array of 511 bytes (255*2+1). So I am
     * supposing a max path of 300 chars. */
    char path[300];
    char buffer[1024];
    int n;
    int fd;
    int root_len;
    int file_len;
    char* file;
    response_t response;
    int is_partial_file;
    time_t now;
    struct stat sb;

    /* Copy the path because we shouldn't edit the variable on the stack */
    file = request->path;
    root_len = strlen(root);
    file_len = strlen(file);

    if (root[0] == '.' && root[1] == '/') {
        root += 2;
        root_len -= 2;
    }

    if (root[root_len - 1] == '/') {
        root_len--;
    }

    /* Considers this kind of path like `/index.html` */
    if (file_len == 1) {
        file = "/index.html";
        file_len = strlen(file);
    }

    strncpy(path, root, root_len);
    strncpy(path + root_len, file, file_len);

    if ((fd = open(path, O_RDONLY)) == -1) {
        perror("Error opening the file on server");
        response = HTTP_404_NOT_FOUND;
        switch (request->http_version) {
        case HTTP1:
            strcpy(buffer, "HTTP/1.0 ");
            break;
        case HTTP1_1:
            strcpy(buffer, "HTTP/1.1 ");
            break;
        case HTTP2:
            strcpy(buffer, "HTTP/2 ");
            break;
        }

        strcpy(buffer + strlen(buffer), response_text(response));
        strcpy(buffer + strlen(buffer), "\n\n");
        write(client, buffer, strlen(buffer));

        return;
    }

    /* The first time search if it raises an error */
    is_partial_file = 0;
    while ((n = read(fd, buffer, sizeof(buffer))) != 0) {
        if (n == -1) {
            is_partial_file = 1;
            break;
        }
    }

    /* The second time send to client the file readed */
    lseek(fd, SEEK_SET, 0);

    /* First line of response */
    response = (is_partial_file) ? HTTP_206_PARTIAL_CONTENT : HTTP_200_OK;
    switch (request->http_version) {
    case HTTP1:
        strcpy(buffer, "HTTP/1.0 ");
        break;
    case HTTP1_1:
        strcpy(buffer, "HTTP/1.1 ");
        break;
    case HTTP2:
        strcpy(buffer, "HTTP/2 ");
        break;
    }

    strcpy(buffer + strlen(buffer), response_text(response));
    strcpy(buffer + strlen(buffer), "\n");
    write(client, buffer, strlen(buffer));

    if (fstat(fd, &sb) != -1) {
        /* Thx to [1]
         * [1] https://www.tutorialspoint.com/c_standard_library/c_function_ctime.htm
         */
        time(&now);
        sprintf(buffer, "Date: %s", ctime(&now));
        write(client, buffer, strlen(buffer));

        sprintf(buffer, "Content-Type: text/txt; charset=UTF-8\n");
        write(client, buffer, strlen(buffer));

        sprintf(buffer, "Content-Length: %ld\n", sb.st_size);
        write(client, buffer, strlen(buffer));

        sprintf(buffer, "Last-Modified: %s", ctime(&sb.st_mtime));
        write(client, buffer, strlen(buffer));

        sprintf(buffer, "Connection: close\n\n");
        write(client, buffer, strlen(buffer));
    }

    while ((n = read(fd, buffer, sizeof(buffer))) != 0) {
        if (n == -1) {
            break;
        }
        buffer[n] = '\0';
        write(client, buffer, strlen(buffer) + 1);
    }

    close(fd);
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

        if (parse_first_line(&request, headers[0], strlen(headers[0])) > -1) {
            if (request.method == GET) {
                read_file(www_path, &request, clientfd);
            }
        }

        for (i = 0; i < headers_num; ++i) {
            free(headers[i]);
        }
        printf("[Connection closed]\n\n");
        close(clientfd);
    }

    close(sockfd);
    return 0;
}
