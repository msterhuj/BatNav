#include <string.h>

user_t * user_list = NULL;
int user_list_size = -1;

user_t * init_new_user(char * name, char * pass) {
    user_t * user = malloc(sizeof(user_t));
    user->name = name;
    user->pass = pass;
    return user;
}

/**
 * @brief Checks if the user is in the list
 * @param name
 * @return
 */
int user_exists(char * name) {
    for (int i = 0; i < user_list_size; i++) {
        if (strcmp(user_list[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Adds a user to the list
 * @param user
 * @return 1 if user early exist, 0 if not
 */
int add_user(user_t * user) {
    if (user_exists(user->name)) return 1;
    user_list_size++;
    user_list = realloc(user_list, sizeof(user_t) * user_list_size);
    user_list[user_list_size - 1] = *user;
    return 0;
}

/**
 * @breif create new instance of user by name and return it
 * @param name
 * @return
 */
user_t * get_user_by_name(char * name) {
    for (int i = 0; i < user_list_size; i++) {
        if (strcmp(user_list[i].name, name) == 0) {
            return init_new_user(user_list[i].name, user_list[i].pass);
        }
    }
    return NULL;
}


void free_user(user_t * user) {
    free(user->name);
    free(user->pass);
    free(user);
}

// todo fix free error
void free_user_list() {
    for (int i = 0; i < user_list_size; i++) {
        free_user(&user_list[i]);
    }
    free(user_list);
    user_list = NULL;
    user_list_size = -1;
}

/**
 * @brief remove user from list
 * @param user_t
 * @return 1 if user not exist, 0 if not
 */
int del_user(user_t * user) {
    for (int i = 0; i < user_list_size; i++) {
        if (user_list[i].name == user->name) {
            free_user(&user_list[i]);
            user_list_size--;
            user_list = realloc(user_list, sizeof(user_t) * user_list_size);
            return 0;
        }
    }
    return 1;
}