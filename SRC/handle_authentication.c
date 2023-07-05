/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "my.h"

void user_authentication(client_request_t *client_request,
server_t *server, int client_index)
{
    if (is_valid_username(client_request->argument)) {
            server->client_list[client_index].auth_status = USER;
            server->client_list[client_index].user_name = true;
            server->client_list[client_index].mdp = false;
            server->client_list[client_index].authentification = false;
            send_response(server, client_index,
            "331 User name okay, need password.\r\n");
        } else {
            send_response(server, client_index,
            "331 User name okay, need password.\r\n");
        }
}

void pass_authentication(client_request_t *client_request,
server_t *server, int client_index)
{
    if (server->client_list[client_index].auth_status == USER &&
        is_valid_password(client_request->argument)) {
        server->client_list[client_index].mdp = true;
        server->client_list[client_index].authentification = true;
        server->client_list[client_index].current_directory = strdup(
        server->server_info.home_path);
        send_response(server, client_index,
        "230 User logged in, proceed.\r\n");
    } else {
        send_response(server, client_index, "530 Login incorrect.\r\n");
    }
}

void handle_authentication(client_request_t *client_request,
server_t *server, int client_index)
{
    if (strcmp(client_request->command, "USER") == 0) {
        user_authentication(client_request, server, client_index);
    } else if (strcmp(client_request->command, "PASS") == 0) {
        pass_authentication(client_request, server, client_index);
    } else {
        send_response(server, client_index,
        "503 Bad sequence of commands.\r\n");
    }
}
