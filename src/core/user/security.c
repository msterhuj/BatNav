
/**
 * 1 true / 0 false
 * @param user
 * @return
 */
int user_is_admin(user_t *user) {
    if (strcasecmp(user->name, "admin") == 0) {
        return 1;
    } return 0;
}

// todo add user auth