#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

FILE * open_user_file(char * mode) {
    FILE * file = fopen("users.bn", mode);
    if (file == NULL) {
        printf("Error opening file users.bn\n");
        exit(1);
    }
    return file;
}

// open file and read all users
void user_init() {
    FILE * fp = open_user_file("r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int n = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            n++;
        }
    }
    fclose(fp);

    user_list = malloc(sizeof(user_t) * n);

    fp = open_user_file("r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int i = 0;
    while (fscanf(fp, "%c:%c:%d", &user_list[i].name, &user_list[i].pass, &user_list[i].is_admin) != EOF) {
        i++;
    }
    fclose(fp);
}
int user_list_size() {
    return sizeof(*user_list) / sizeof(user_t);
}

// save all users to file
void user_save() {
    FILE * fp = open_user_file("w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < user_list_size(); i++) {
        fprintf(fp, "%c:%c:%d\n", user_list[i].name, user_list[i].pass, user_list[i].is_admin);
    }
    fclose(fp);
}

void user_reload() {
    user_save();
    free(user_list);
    user_list = NULL;
    user_init();
}