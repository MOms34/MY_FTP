/*
** EPITECH PROJECT, 2023
** momo
** File description:
** client
*/

#ifndef MYY_H
    #define MYY_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <ctype.h>
    #define MAX_CLIENTS 9
    #define BUFFER_SIZE 1024
    #define MAX_USERNAME_LENGTH 50
    #define MAX_PASSWORD_LENGTH 50
    #define MAX_PATH_LENGTH 200
    #define MAX_COMMAND_LENGTH 5
    #define MAX_ARGUMENT_LENGTH 50

typedef enum {
    OFFLINE,
    USER,
    CONNECTED
} authentification_t;

typedef enum {
    ACTIVE,
    PASSIVE
} data_transfert_mode_t;

typedef struct {
    int port;
    char *home_path;
    bool active;
} server_info_t;

typedef struct {
    int control_sockfd;
    struct sockaddr_in control_sockaddr;
    int data_sockfd;
    struct sockaddr_in data_sockaddr;
    authentification_t auth_status;
    char *current_directory;
    data_transfert_mode_t data_transfert_mode;
    bool is_data_socket_open;
    bool user_name;
    bool mdp;
    bool authentification;
} client_info_t;

typedef struct {
    char *command;
    char *argument;
} client_request_t;

typedef struct {
    int sockfd;
    struct sockaddr_in sockaddr;
} connection_info_t;

typedef struct {
    int listen_sockfd;
    server_info_t server_info;
    fd_set active_fd_set;
    client_info_t *client_list;
    int max_clients;
} server_t;

void print_error(char *str);
int all_init(int ac, char **argv);
void initialize_client(server_t *server, int client_index, int newsockfd);
void connect_client(server_t *server, int client_i, int newsock);
void print_help(void);
int is_number(const char *str);
int check_arg(int ac, char **argv, server_info_t *this);
int creat_socket(void);
void server_loop(server_t *server);
int create_server_socket(server_info_t *server_info);
void init_server(server_t *server, server_info_t *server_info, int max_clients);
void accept_client_connection(server_t *server);
void disconnect_client(server_t *server, int client_index);
void handle_client_request(server_t *server, int client_index);
void handle_client_command(client_request_t *client_request, server_t *server,
int client_index);
void handle_authentication(client_request_t *client_request, server_t *server,
int client_index);
void send_response(server_t *server, int client_index, char *response);
void send_data(int sockfd, char *buffer, int size);
void receive_data(int sockfd, char *buffer, int size);
void tokenize_client_request(char *client_request_str,
client_request_t *client_request);
void get_client_argument(char *client_request_str, char *argument);
bool is_valid_username(char *username);
bool is_valid_password(char *password);
bool is_valid_path(char *path);
bool is_valid_port(char *port_str);
int setup_data_socket(server_t *server, int client_index);
void close_data_socket(server_t *server, int client_index);
void send_file(int data_sockfd, char *file_path);
void receive_file(int data_sockfd, char *file_path);
int handle_client_command2(client_request_t *client_request,
server_t *server, int client_index, char *command);
int handle_other_cmd(client_request_t *client_request,
server_t *server, int client_index, char *cmd);
int handle_other_cmd2(client_request_t *client_request,
server_t *server, int client_index, char *cmd);

#endif /* MYY_H */
