#include "../commands/commands.h"

struct sockaddr_in newAddr;
socklen_t addr_size;
int socket_client_fd;
pid_t child_pid;

void wait_connection_from_client() {
    socket_client_fd = accept(socket_fd, (struct sockaddr *) &newAddr, &addr_size);
    if (socket_client_fd < 0) {
        printf("Error accepting connection from client\n");
        exit(1);
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
}

void register_client_connection() {
    child_pid = fork();
    if (child_pid < 0) {
        printf("Error forking child process\n");
        exit(1);
    }
    close(socket_fd);
}

void handle_client_connection() {
    char buffer[1024];
    while (1) {
        recv(socket_client_fd, buffer, 1024, 0);
        if (strcmp(buffer, ":exit") == 0) {
            printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
            close(socket_client_fd);
            exit(0);
        } else {
            char * prompt = ">>>";
            handle_command(buffer);
            send(socket_client_fd, prompt, strlen(prompt), 0);
            bzero(buffer, sizeof(buffer));
        }
    }
}

void send_message_to_client(char *message) {
    send(socket_client_fd, message, strlen(message), 0);
}