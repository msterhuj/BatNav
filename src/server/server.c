#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../core/core.h"

void run_server(int port) {

    setup_users();

    init_socket();
    bind_socket(port);
    listen_socket();

    while (1) {
        wait_connection_from_client();
        register_client_connection();
        handle_client_connection();
    }
}