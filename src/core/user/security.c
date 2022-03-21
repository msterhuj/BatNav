
int user_is_admin(user_t *user) {
    return strcasecmp(user->name, "admin");
}