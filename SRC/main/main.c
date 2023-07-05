/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/


#include "my.h"

void print_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous user");
    printf("\n");
}

int all_init(int ac, char **argv)
{
    server_t *server = malloc(sizeof(server_t));
    server_info_t *server_info = malloc(sizeof(server_info_t));

    if (server_info == NULL)
        return 84;
    if (check_arg(ac, argv, server_info) != 0)
        return 84;
    init_server(server, server_info, 100);
    server_loop(server);
    return 0;
}

int main(int ac, char **argv)
{
    if (ac == 2 && strcmp(argv[1], "-help") == 0) {
        print_help();
        EXIT_SUCCESS;
    }
    if (all_init(ac, argv) != 0)
        return 84;
    return 0;
}
