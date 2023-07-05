/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** ftp
*/

#include "my.h"

int creat_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int optval = 1;

    if (sockfd == -1) {
        print_error("socket_t creation have Failed.\n");
        return -1;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval,
    sizeof(optval)) == -1) {
        print_error("Failed to set socket options");
        return -1;
    }
    return sockfd;
}

int handle_other_cmd2(client_request_t *client_request,
server_t *server, int client_index, char *cmd)
{
    if (strncmp(cmd, "NOOP", 4) == 0) {
        send_response(server, client_index,
        "200 Command okay.\n");
        return 1;
    }
    if (strncmp(cmd, "CWD", 3) == 0) {
        if (chdir(client_request->argument) != 0) {
            send_response(server, client_index,
            "550 Failed to change directory.\n");
        } else {
            send_response(server, client_index,
            "250 Directory successfully changed.\n");
            server->client_list[client_index].current_directory
            = client_request->argument;
        }
        return 1;
    }
    return 0;
}

int handle_other_cmd(client_request_t *client_request,
server_t *server, int client_index, char *cmd)
{
    char response[BUFFER_SIZE];

    if (strncmp(cmd, "HELP", 4) == 0) {
        send_response(server, client_index,
        "   HELP PWD USER PASS QUIT\n");
        send_response(server, client_index,
        "214 Help message.\n");
        return 1;
    }
    if (strncmp(cmd, "PWD", 3) == 0 &&
    server->client_list[client_index].authentification == true) {
        snprintf(response, BUFFER_SIZE, "257 \"%s\" PWD.\n",
        server->client_list[client_index].current_directory);
        send_response(server, client_index, response);
        return 1;
    }
    if (handle_other_cmd2(client_request, server, client_index, cmd) == 1)
        return 1;
    return 0;
}
