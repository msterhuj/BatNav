#include <sys/types.h>

typedef struct {
    int * fd;
    pid_t * pid;
    int * status; // 0 - not connected, 1 - connected
    user_t * user;
} connection_t;

connection_t * connection_list = NULL;
int connection_list_size = 0;

connection_t init_new_connection(int fd, pid_t pid) {
    connection_t new_connection;
    new_connection.fd = malloc(sizeof(int));
    new_connection.pid = malloc(sizeof(pid_t));
    new_connection.status = malloc(sizeof(int));
    new_connection.user = malloc(sizeof(user_t));
    *new_connection.fd = fd;
    *new_connection.pid = pid;
    *new_connection.status = 0;
    return new_connection;
}

void add_connection(int fd, pid_t pid) {
    connection_t new_connection = init_new_connection(fd, pid);
    connection_list = realloc(connection_list, sizeof(connection_t) * (connection_list_size + 1));
    connection_list[connection_list_size] = new_connection;
    connection_list_size++;
}

void set_user_to_connection(int fd, user_t user) {
    for (int i = 0; i < connection_list_size; i++) {
        if (*connection_list[i].fd == fd) {
            *connection_list[i].user = user;
            break;
        }
    }
}