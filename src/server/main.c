#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int arc, char* argv[]) {
    struct addrinfo hints;
    struct addrinfo* servinfo;
    struct addrinfo* p;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // get address info of the IP address specified in parameter
    status = getaddrinfo(argv[1], NULL, &hints, &servinfo);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // since it's a linked list, loop through the nodes
    for (p = servinfo; p != NULL; p = p->ai_next) {
        // get the IP address in the struct sockaddr to easily access the
        // properties of this socket

        char addr_string[INET6_ADDRSTRLEN];
        void* addr;
        char* ipver;

        if (p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            ipver = "IPv4";
            addr = &(ipv4->sin_addr);
            // inet_ntop(AF_INET, addr, addr_string, INET_ADDRSTRLEN);
        } else if (p->ai_family == AF_INET6) {
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            ipver = "IPv6";
            addr = &(ipv6->sin6_addr);
            // inet_ntop(AF_INET6, addr, addr_string, INET6_ADDRSTRLEN);
        }

        // or we can get the address out here and just use the family as signal
        inet_ntop(p->ai_family, addr, addr_string, sizeof addr_string);
        printf("protocol: %s with address: %s\n", ipver, addr_string);
    }

    freeaddrinfo(servinfo);
}
