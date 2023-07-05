/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "my.h"

int is_number(const char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (!isdigit(str[i])) {
            return -1;
        }
        i++;
    }
    return 0;
}

int check_arg(int ac, char **argv, server_info_t *this)
{
    if (ac != 3)
        return 84;
    if (is_number(argv[1]) == 0)
        this->port = atoi(argv[1]);
    else
        return 84;
    if (this->port < 1 || this->port > 65535)
        return 84;
    if (access(argv[2], R_OK | W_OK) == -1)
        return 84;
    else
        this->home_path = argv[2];
    return 0;
}

bool is_valid_username(char *username)
{

    if (strlen(username) == 0) {
        return false;
    }
    if (strcmp(username, "Anonymous") == 0) {
        return true;
    } else
        return false;
}

bool is_valid_password(char *password)
{
    if (strlen(password) == 0) {
        return true;
    }
    return false;
}

bool is_valid_path(char *path)
{
    char *token;
    char copy_path[MAX_PATH_LENGTH];

    if (path[0] != '/')
        return false;
    strcpy(copy_path, path);
    token = strtok(copy_path, "/");
    while (token != NULL) {
        if (strlen(token) > MAX_PATH_LENGTH) {
            return false;
        }
        token = strtok(NULL, "/");
    }
    if (strlen(path) > MAX_PATH_LENGTH) {
        return false;
    }
    return true;
}
