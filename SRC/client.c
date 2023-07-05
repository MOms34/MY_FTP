/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "my.h"

void tokenize_client_request(char *client_request_str,
client_request_t *client_request)
{
    char *tokens[MAX_COMMAND_LENGTH];
    int i = 0;
    char *token = strtok(client_request_str, " ");

    while (token != NULL && i < MAX_COMMAND_LENGTH) {
        tokens[i] = strdup(token);
        token = strtok(NULL, " ");
        i++;
    }
    client_request->command = strdup(tokens[0]);
    if (i > 1) {
        client_request->argument = strdup(tokens[1]);
        client_request->argument[strlen(client_request->argument) - 2] = '\0';
    } else {
        client_request->argument = NULL;
    }
    for (int j = 0; j < i; j++) {
        free(tokens[j]);
    }
}

int handle_client_command2(client_request_t *client_request,
server_t *server, int client_index, char *command)
{
    if (strcmp(command, "USER") == 0) {
        handle_authentication(client_request, server, client_index);
        return 1;
    }
    if (strcmp(command, "PASS") == 0) {
        handle_authentication(client_request, server, client_index);
        return 1;
    }
    if (strcmp(command, "SYST") == 0 &&
    server->client_list[client_index].authentification == true) {
        send_response(server, client_index, "215 UNIX Type: L8\n");
        return 1;
    }
    return 0;
}

void handle_client_command(client_request_t *client_request,
server_t *server, int client_index)
{
    char *command = client_request->command;

    if (handle_client_command2(client_request, server,
    client_index, command) == 1)
        return;
    if (server->client_list[client_index].authentification == true &&
    handle_other_cmd(client_request, server, client_index, command) == 1) {
    } else if (server->client_list[client_index].authentification != true) {
        send_response(server, client_index,
        "530 please login\n");
    } else {
        send_response(server, client_index,
        "500 Syntax error, command unrecognized.\n");
    }
}
