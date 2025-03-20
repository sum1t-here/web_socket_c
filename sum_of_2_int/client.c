#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    int num1, num2, sum;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Get two numbers from the user
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // Convert to network byte order and send to server
    num1 = htonl(num1);
    num2 = htonl(num2);
    sendto(sockfd, &num1, sizeof(num1), 0, (struct sockaddr *)&server_addr, addr_len);
    sendto(sockfd, &num2, sizeof(num2), 0, (struct sockaddr *)&server_addr, addr_len);

    // Receive result from server
    recvfrom(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&server_addr, &addr_len);
    sum = ntohl(sum);

    printf("Sum received from server: %d\n", sum);

    close(sockfd);
    return 0;
}
