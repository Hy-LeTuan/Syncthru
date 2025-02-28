#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MYPORT "1200"
#define BACKLOG 10

void client() {
    int status;
    struct addrinfo hints;
    struct addrinfo* servinfo;
    struct addrinfo* selfinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int signal = getaddrinfo(NULL, "1200", &hints, &servinfo);

    if (getaddrinfo(NULL, "1200", &hints, &servinfo) == 0 &&
        getaddrinfo(NULL, "1300", &hints, &selfinfo) == 0) {
        int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                            servinfo->ai_protocol); // configure local port
        bind(sockfd, selfinfo->ai_addr, selfinfo->ai_addrlen);

        if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
            printf("connection failed\n");
            exit(-1);
        }
        printf("connection established");
    }
}

int main() {
    int status;
    struct addrinfo hints;
    struct addrinfo* servinfo;
    int sockfd;

    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int new_fd;
    char buffer;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // this is your own IP address

    status = getaddrinfo(NULL, MYPORT, &hints, &servinfo);

    if (status == 0) {
        sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                        servinfo->ai_protocol);
        int opt = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
        bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
        listen(sockfd, BACKLOG); // listen on port 1200;

        addr_size = sizeof their_addr;
        printf("reached this line\n");
        new_fd = accept(sockfd, (struct sockaddr*)&their_addr,
                        &addr_size); // awaiting new connections
        printf("reached new line\n");

        if (new_fd == -1) {
            printf("connection failed\n");
        } else {
            printf("connection succeeded\n");
        }
    } else {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
}
