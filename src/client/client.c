#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void run_client(char *host, int port) {

    int socket_client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_client_fd < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Client Socket is created.\n");

    struct sockaddr_in server_address;
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(host);

    int connection_result = connect(socket_client_fd, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_result < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Connected to Server.\n");

    char buffer[1024];
    while (1) {
        printf("Client: \t");
        scanf("%s", &buffer[0]);
        send(socket_client_fd, buffer, strlen(buffer), 0);

        if (strcmp(buffer, ":exit") == 0) {
            close(socket_client_fd);
            printf("Disconnected from server.\n");
            exit(1);
        }

        if (recv(socket_client_fd, buffer, 1024, 0) < 0) printf("Error in receiving data.\n");
        else printf("Server: \t%s\n", buffer);
    }
}