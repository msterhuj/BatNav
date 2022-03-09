#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * user list on file stored like this:
 * user:pass:isAdmin
 */

typedef struct {
    char name;
    char pass;
    int is_admin;
} user_t;

user_t * user_list = NULL;
