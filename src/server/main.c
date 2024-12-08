#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int status;
    struct addrinfo hints;
    struct addrinfo* servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, "443", &hints, &servinfo);

    if (status == 0) {
        printf("protocol: %d\n", servinfo->ai_family);
        printf("protocol for ipv4: %d\n", AF_INET);
        printf("protocol for ipv6: %d\n", AF_INET6);

        struct sockaddr_in6* ipv6 = (struct sockaddr_in6 *) servinfo->ai_addr;

        void* addr = &(ipv6->sin6_addr);

        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(servinfo->ai_family, addr, ipstr, sizeof(ipstr));
        printf("ip address: %s\n", ipstr);

    } else {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

}
