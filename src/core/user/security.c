
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
int user_auth(char *user_name,char *user_pass){
    user_t *user=get_user_by_name(user_name);
    if(strcmp(user_pass,user->pass)==0){
        return 1;
    }
    else{
        return 0;
    }

}