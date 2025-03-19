## UDP Socket programming in C

- ### Prequisite
    - #### What is a Socket ?
        A socket is an endpoint for communication between two machines.
        - ```TCP``` sockets provide reliable, connection-oriented communication.
        - ```UDP``` sockets provide faster, connectionless communication.
    - #### What is UDP ?
        UDP (User Datagram Protocol) is:
        - Faster than TCP (no handshake)
        - Connectionless (doesn’t establish a connection before sending data)
        - Unreliable (packets may be lost or arrive out of order)
        - Used for video streaming, gaming, DNS, etc.
- ### Libraries required for socket programming
    To use sockets in C, include these headers:
    ```c
        #include <stdio.h>       // For input-output functions like printf, fgets
        #include <stdlib.h>      // For memory allocation and exit() function
        #include <string.h>      // For string operations like memset and strlen
        #include <unistd.h>      // For close() function
        #include <arpa/inet.h>   // For networking functions (inet_addr, htons)
        #include <sys/socket.h>  // For socket functions (socket, sendto)
    ```

### <u>[Basic UDP Socket Program](./basic_udp_socket)</u>

- #### Step-by-Step Breakdown of UDP Client Code
    - Create a UDP Socket
        ```c
            sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        ```
        - ```AF_INET``` -> IPv4 address family
        - ```SOCK_DGRAM``` -> UDP socket type
        - ```0``` ->  Default protocol for UDP
    - Define Server Address
        ```c
            struct sockaddr_in server_addr;
            memset(&server_addr, 0, sizeof(server_addr));  // Clear structure
            server_addr.sin_family = AF_INET;  // IPv4
            server_addr.sin_port = htons(PORT);  // Convert port to network byte order
            server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP
        ```
        - ```memset()``` -> Clears memory to avoid garbage values
        - ```sin_family = AF_INET``` -> We are using IPv4
        - ```sin_port = htons(PORT)``` -> Converts port number to network byte order (Big Endian)
        - ```inet_addr("127.0.0.1")``` -> Converts IP to network format (localhost)
    - Take User Input and Send Data
        ```c
            printf("Enter message: ");
            fgets(buffer, BUFFER_SIZE, stdin);  // Read input from the user
            buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len);

        ```

        - ```fgets()``` -> Reads user input into buffer
        - ```strcspn()``` -> Removes the newline character from input
        - ```sendto()``` -> Sends data using UDP
            - ```sockfd``` -> Socket descriptor
            - ```buffer``` -> Message to send
            - ```strlen(buffer)``` -> Message length
            - ```0``` -> Default flags
            - ```server_addr``` -> Address of the receiver
            - ```addr_len``` -> Size of the address structure

- ### Step-by-Step Breakdown of UDP Server Code
    - Create a UDP Socket
        ```c
            sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        ```
    - Define Server Address
        ```c
            struct sockaddr_in server_addr;
            memset(&server_addr, 0, sizeof(server_addr));  // Clear structure
            server_addr.sin_family = AF_INET;  // IPv4
            server_addr.sin_port = htons(PORT);  // Convert port to network byte order
            server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP
        ```

    - Bind the Socket
        ```c
            bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
        ```
        - ```bind()``` attaches the socket to the specified IP address and port so that it can listen for incoming messages.
    - Receive Data from Client
        ```c
            recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &addr_len);
            printf("Message received from client: %s \n", buffer);
        ```
        - ```recvfrom()``` -> Receives data using UDP
        - ```sockfd``` -> Socket descriptor
        - ```buffer``` -> Message storage
        - ```BUFFER_SIZE``` -> Maximum data to receive
        - ```0``` → Default flags
        - ```client_addr``` -> Client’s address structure (sender info)
        - ```addr_len``` -> Size of the client address structure
    - Close the Socket

