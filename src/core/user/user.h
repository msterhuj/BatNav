#ifndef BATNAV_USER_H
#define BATNAV_USER_H

typedef struct {
    // data stored in file
    char * name;
    char * pass;
} user_t;

int user_exists(char * name);
int add_user(user_t * user);
user_t * get_user_by_name(char * name);
void free_user(user_t * user);
void free_user_list();
int del_user(user_t * user);

FILE * open_user_file(char * mode);
int get_user_count_in_file();
void save_users();
void user_reload();

int user_is_admin(user_t *user);

#include "user.c"
#include "loader.c"
#include "security.c"

#endif //BATNAV_USER_H
