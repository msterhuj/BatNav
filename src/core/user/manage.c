#include "user.h"

user_t * init_user(char * name, char * pass) {
    user_t * user = malloc(sizeof(user_t));
    user->name = name;
    user->pass = pass;
    return user;
}

void create_user(user_t *user) {
    printf("%lu", sizeof(*user_list));
    user_list = realloc(user_list, sizeof(user_t) * (user_list_size() + sizeof(user_t)));
    printf("%lu", sizeof(*user_list));
    user_list[(sizeof(user_list) / sizeof(user_t)) - sizeof(user_t)] = *user;
    //user_list = realloc(user_list, sizeof(user_t) * (sizeof(*user_list) + 1));
    //user_list[sizeof(*user_list) - 1] = *user;
}

user_t * get_user_by_name(char * name) {
    for (int i = 0; i < sizeof(*user_list); i++) {
        if (user_list[i].name == name) {
            return &user_list[i];
        }
    }
    return NULL;
}

void delete_user(user_t *user) {
    int i;
    for (i = 0; i < sizeof(*user_list); i++) {
        if (user_list[i].name == user->name) {
            user_list[i] = user_list[sizeof(*user_list) - 1];
            user_list = realloc(user_list, sizeof(*user_list) - 1);
            return;
        }
    }
}