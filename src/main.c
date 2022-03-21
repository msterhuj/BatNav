#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "server/server.h"
#include "client/client.h"

void print_parameters_help();

int main(int argc, char *argv[]) {
    char *host = "127.0.0.1";
    int port = 6969;

    if (argc > 1) {
        if (strcmp(argv[1], "help") == 0) print_parameters_help();

        else if (strcmp(argv[1], "server") == 0) {
            if (argc > 2) port = atoi(argv[2]);

            if (port > 0 && port < 65535) run_server(port);
            else puts("Invalid port number (1-65535)");
        }

        else if (strcmp(argv[1], "client") == 0) {
            if (argc > 2) host = argv[2];
            if (argc > 3) port = atoi(argv[3]);

            if (port > 0 && port < 65535) run_client(host, port);
            else puts("Invalid port number (1-65535)");
        }

        else puts("Invalid parameter");

    } else print_parameters_help();

    // always run
    user_init();
    int size = 0;

    while (user_list[size].name != NULL) {
        if (user_list[size].name == NULL) {
            break;
        }
        //printf("%s\n", user_list[size].name);
        printf("%d", size);
        size++;
    }
    //printf("%d\n", size);
    //int beteu = sizeof (user_list[0]) / sizeof (user_list);
    //printf("%d\n", beteu);


    // print all user of user_list

    // end

    return 0;
}

void print_parameters_help() {
    puts("Usage: ./BatNav <parameter>");
    puts("Parameters:");
    puts("\thelp - print this help");
    puts("\tserver <port> - start server on port (default: 6969)");
    puts("\tclient <host> <port> - connect to server (default: 127.0.0.1 6969)");
}