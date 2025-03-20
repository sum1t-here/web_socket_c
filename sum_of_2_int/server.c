#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // create udp socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bind socket to address
    bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("UDP Server listening on port %d\n", PORT);

     while (1) {
        int num1, num2, sum;

        // Receive numbers from client
        recvfrom(sockfd, &num1, sizeof(num1), 0, (struct sockaddr *)&client_addr, &addr_len);
        recvfrom(sockfd, &num2, sizeof(num2), 0, (struct sockaddr *)&client_addr, &addr_len);

        num1 = ntohl(num1);
        num2 = ntohl(num2);
        sum = num1 + num2;

        printf("Received numbers: %d and %d\n", num1, num2);
        printf("Sending sum: %d\n", sum);

        // Send result back to client
        sum = htonl(sum);
        sendto(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}