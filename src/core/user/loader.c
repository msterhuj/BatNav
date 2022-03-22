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

/**
 * @brief get number of users in file
 * @return int
 */
int get_user_count_in_file() {
    FILE * file = open_user_file("r");
    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    fclose(file);
    return count;
}

/**
 * @brief Load all users from file and allocate memory for them
 */
void setup_users() {
    user_list_size = get_user_count_in_file();
    user_list = malloc(sizeof(user_t) * user_list_size);
    if (user_list == NULL) {
        printf("Error: can't allocate memory for users\n");
        exit(1);
    }

    FILE * file = open_user_file("r");
    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char * pch = strtok(line, "\n");
        pch = strtok(pch, ":");
        user_list[i].name = malloc(strlen(pch) + 1);
        strcpy(user_list[i].name, pch);
        pch = strtok(NULL, ":");
        user_list[i].pass = malloc(strlen(pch) + 1);
        strcpy(user_list[i].pass, pch);
        i++;
    }
    fclose(file);
    printf("%d users loaded\n", i);
}


// save all users to file
void save_users() {
    FILE * fp = open_user_file("w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < user_list_size; i++) {
        printf("saving -> %s:%s\n", user_list[i].name, user_list[i].pass);
        fprintf(fp, "%s:%s\n", user_list[i].name, user_list[i].pass);
    }
    fclose(fp);
}

void user_reload() {
    free_user_list();
    setup_users();
}