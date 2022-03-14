
void connect_user(user_t *user) {
    connected_users = realloc(connected_users, sizeof (user_t) * (sizeof(*connected_users) + 1));
    connected_users[sizeof (*connected_users) - 1] = *user;
}

void disconnect_user(user_t *user) {
    int i;
    for (i = 0; i < sizeof(*connected_users); i++) {
        if (connected_users[i].name == user->name) {
            connected_users[i] = connected_users[sizeof(*connected_users) - 1];
            connected_users = realloc(connected_users, sizeof(*connected_users) - 1);
            return;
        }
    }
}

int user_is_connected(user_t *user) {
    int i;
    for (i = 0; i < sizeof(*connected_users); i++) {
        if (connected_users[i].name == user->name) {
            return 1;
        }
    }
    return 0;
}

int user_is_admin(user_t *user) {
    return strcasecmp(user->name, "admin");
}

int auth_user(char * user, char * pass) {
    user_t * user_data = get_user_by_name(user);
    if (user_data == NULL) {
        return 0;
    }
    if (strcmp(user_data->pass, pass) == 0) {
        pause();
        return 1;
    } return 0;
}