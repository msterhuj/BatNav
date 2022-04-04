#include "../connections/connection.h"

int *grid=NULL;
int gridSize=0;
int nb_boat=0;

int handle_command(char * buffer,int socket_client_fd) {
    printf("HANDLE %s\n", buffer);
    printf("HANDLE %s\n", buffer);
    user_t *user = init_new_user("", "");
    setup_users();
    char prompt[1048];
    char *token=strtok(buffer, " ");
    if (strcmp(token, "auth") == 0) {
        printf("passe le AUTH");
        token=strtok(buffer, " ");
        char *name=token;
        if (user_exists(token) == 1) {
            printf("passe le NAME");
            token=strtok(buffer, " ");
            if (user_auth(name, token)) {
                printf("passe le PASS");
                strcpy(prompt, "Authentification réussi");
                send(socket_client_fd, prompt, strlen(prompt), 0);
            }

        }


        return -1;
    }


}