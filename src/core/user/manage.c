#include "user.h"

user_t * user_new(char name, char pass, int is_admin) {
    user_t * user = malloc(sizeof(user_t));
    user->name = name;
    user->pass = pass;
    user->is_admin = is_admin;
    return user;
}

void add_user(user_t *user) {
    user_list = realloc(user_list, sizeof(user_t) * (sizeof(user_list) + 1));
    user_list[sizeof(user_list) - 1] = *user;
}

user_t * get_user_by_name(char name) {
    for (int i = 0; i < sizeof(user_list); i++) {
        if (user_list[i].name == name) {
            return &user_list[i];
        }
    }
    return NULL;
}

void remove_user(user_t *user) {
    int i;
    for (i = 0; i < sizeof(user_list); i++) {
        if (user_list[i].name == user->name) {
            user_list[i] = user_list[sizeof(user_list) - 1];
            user_list = realloc(user_list, sizeof(user_list) - 1);
            return;
        }
    }
}

int user_exists(char name) {
    for (int i = 0; i < sizeof(user_list); i++) {
        if (user_list[i].name == name) {
            return 1;
        }
    }
    return 0;
}

int user_is_admin(char name) {
    for (int i = 0; i < sizeof(user_list); i++) {
        if (user_list[i].name == name) {
            return user_list[i].is_admin;
        }
    }
    return 0;
}