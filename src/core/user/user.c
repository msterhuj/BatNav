#include <string.h>
#include <sys/types.h>

/**
 * user list on file stored like this:
 * user:pass
 */

typedef struct {
    // data stored in file
    char * name;
    char * pass;
} user_t;

user_t * user_list = NULL;