#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

#define USER_FILE_NAME "user.dat"

/**
 * @brief Return file pointer of user.dat or create new file
 *        if not exist with default admin user
 * @param mode
 * @return FILE *
 */
FILE * open_user_file(char * mode) {
    FILE * file = fopen(USER_FILE_NAME, mode);
    if (file == NULL) {
        file = fopen(USER_FILE_NAME, "w");
        if (file == NULL) {
            printf("Error: can't open file users.bn\n");
            exit(1);
        }
        fprintf(file, "admin:admin\n");
        fclose(file);
        return open_user_file(mode);
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
    while (fscanf(fp, "%c:%c", user_list[i].name, user_list[i].pass) != EOF) {
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
        fprintf(fp, "%s:%s\n", user_list[i].name, user_list[i].pass);
    }
    fclose(fp);
}

void user_reload() {
    user_save();
    free(user_list);
    user_list = NULL;
    user_init();
}