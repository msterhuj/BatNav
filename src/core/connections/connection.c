#include <sys/types.h>

typedef struct {
    int * fd;
    pid_t * pid;
    int * status; // 0 - not connected, 1 - connected
    user_t * user;
} connection;

connection * connection_list = NULL;