/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "my.h"

void disconnect_client(server_t *server, int client_index)
{
    close(server->client_list[client_index].control_sockfd);
    server->client_list[client_index].control_sockfd = -1;
    close(server->client_list[client_index].data_sockfd);
    server->client_list[client_index].data_sockfd = -1;
    free(server->client_list[client_index].current_directory);
    server->client_list[client_index].current_directory = NULL;
    server->client_list[client_index].auth_status = OFFLINE;
    server->client_list[client_index].data_transfert_mode = ACTIVE;
    server->client_list[client_index].is_data_socket_open = false;
}

void send_response(server_t *server, int client_index, char *response)
{
    int control_sockfd = server->client_list[client_index].control_sockfd;

    if (write(control_sockfd, response, strlen(response)) < 0) {
        print_error("Erreur lors de l'envoi de la réponse au client");
        disconnect_client(server, client_index);
    }
}

void handle_client_request(server_t *server, int client_index)
{
    char client_request_str[BUFFER_SIZE] = "";
    int control_sockfd = server->client_list[client_index].control_sockfd;
    int n = read(control_sockfd, client_request_str, BUFFER_SIZE);

    if (n < 0) {
        print_error("Erreur lors de la lecture de la requête client");
        return;
    } else if (n == 0) {
        disconnect_client(server, client_index);
        return;
    } else {
        client_request_t client_request;
        tokenize_client_request(client_request_str, &client_request);
        handle_client_command(&client_request, server, client_index);
    }
}
