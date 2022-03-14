int socket_fd;
struct sockaddr_in serverAddr;

void init_socket() {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Server Socket is created.\n");
}

void bind_socket(int port) {
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket_fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error in binding.\n");
        exit(1);
    }
    printf("Server Socket is binded.\n");
}

void listen_socket() {
    if (listen(socket_fd, 10) == 0)
        printf("Listening....\n");
    else {
        printf("Error in binding.\n");
        exit(1);
    }
}
