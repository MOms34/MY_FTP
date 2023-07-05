/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "my.h"

void initialize_client(server_t *server, int client_index, int newsockfd)
{
    server->client_list[client_index].control_sockfd = newsockfd;
    server->client_list[client_index].auth_status = OFFLINE;
    server->client_list[client_index].current_directory =
    strdup(server->server_info.home_path);
    server->client_list[client_index].data_transfert_mode = PASSIVE;
    server->client_list[client_index].is_data_socket_open = false;
    server->client_list[client_index].user_name = false;
    server->client_list[client_index].mdp = false;
}

void connect_client(server_t *server, int client_i, int newsock)
{
    fd_set read_fd_set;

    close(server->listen_sockfd);
    initialize_client(server, client_i, newsock);
    send_response(server, client_i, "220 Service ready for new user.\r\n");
    while (1) {
        FD_ZERO(&read_fd_set);
        FD_SET(server->client_list[client_i].control_sockfd, &read_fd_set);
        if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) == -1) {
            print_error("Client disconect");
            exit(EXIT_FAILURE);
        }
        if (FD_ISSET(server->client_list[client_i].control_sockfd,
        &read_fd_set)) {
            handle_client_request(server, client_i);
        }
    }
    exit(0);
}

void process_client(server_t *server, int client_index, int newsockfd)
{
    pid_t pid = fork();
    if (pid == -1) {
        print_error("Error creating child process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        connect_client(server, client_index, newsockfd);
    } else {
        close(newsockfd);
    }
}

void accept_client_connection(server_t *server)
{
    int newsockfd = accept(server->listen_sockfd, NULL, NULL);
    int client_index = 0;

    if (newsockfd == -1) {
        print_error("Error accepting connection");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < server->max_clients; i++) {
        if (server->client_list[i].control_sockfd == -1) {
            client_index = i;
            break;
        }
    }
    if (client_index == -1) {
        print_error("Too many clients");
        close(newsockfd);
        return;
    }
    process_client(server, client_index, newsockfd);
}
