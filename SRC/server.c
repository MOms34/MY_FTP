/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "my.h"

int create_server_socket(server_info_t *server_info)
{
    int sockfd = creat_socket();
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_info->port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr*)&server_addr,
    sizeof(server_addr)) == -1) {
        print_error("Failed to bind socket");
        return -1;
    }
    if (listen(sockfd, SOMAXCONN) == -1) {
        print_error("Failed to listen on socket");
        return -1;
    }
    return sockfd;
}

void init_server(server_t *server, server_info_t *server_info, int max_clients)
{
    server->server_info = *server_info;
    server->max_clients = max_clients;
    server_info->active = true;
    server->listen_sockfd = create_server_socket(server_info);
    server->active_fd_set = (fd_set){0};
    server->client_list =
    (client_info_t*)malloc(max_clients * sizeof(client_info_t));
    if (server->client_list == NULL) {
        print_error("Failed to allocate memory for client list");
        exit(84);
    }
    for (int i = 0; i < max_clients; i++) {
        server->client_list[i] = (client_info_t){0};
    }
    FD_ZERO(&server->active_fd_set);
    FD_SET(server->listen_sockfd, &server->active_fd_set);
}

void descriptor_list(server_t *server, fd_set read_fd_set)
{
    for (int i = 0; i < server->max_clients; i++) {
        if (FD_ISSET(server->client_list[i].control_sockfd,
        &read_fd_set)) {
            handle_client_request(server, i);
        }
    }
}

void request(server_t *server, fd_set read_fd_set)
{
    for (int i = 0; i < server->max_clients; i++) {
        if (FD_ISSET(server->listen_sockfd, &read_fd_set)) {
            accept_client_connection(server);
        }
        if (server->client_list[i].auth_status == CONNECTED &&
        FD_ISSET(server->client_list[i].control_sockfd, &read_fd_set)) {
            handle_client_request(server, i);
        }
    }
}

void server_loop(server_t *server)
{
    while (1) {
        fd_set read_fd_set = server->active_fd_set;

        if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) == -1) {
            print_error("Error in select() function");
            exit(EXIT_FAILURE);
        }

        request(server, read_fd_set);
    }
}
