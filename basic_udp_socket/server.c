#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create a UDP Socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket
    bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("UDP Server running on port %d \n", PORT);

    // Receive message from client
    recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &addr_len);
    printf("Message receive from clinet: %s \n", buffer);

    close(sockfd);
    return 0;
}