#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../core/user/user.h"

void run_server(int port) {
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Server Socket is created.\n");

    struct sockaddr_in serverAddr;
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int bind_result = bind(socket_fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (bind_result < 0) {
        printf("Error in binding.\n");
        exit(1);
    }
    printf("Bind to port %d\n", port);

    if (listen(socket_fd, 10) == 0) printf("Listening....\n");
    else printf("Error in binding.\n");

    while (1) {

        struct sockaddr_in newAddr;
        socklen_t addr_size;

        char buffer[1024];

        int socket_client_fd = accept(socket_fd, (struct sockaddr *) &newAddr, &addr_size);
        if (socket_client_fd < 0) {
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        pid_t child_pid = fork();
        if (child_pid == 0) {
            close(socket_fd);

            while (1) {
                recv(socket_client_fd, buffer, 1024, 0);
                if (strcmp(buffer, ":exit") == 0) {
                    printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    close(socket_client_fd);
                    break;
                } else {
                    printf("Client: %s\n", buffer);
                    send(socket_client_fd, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }
}