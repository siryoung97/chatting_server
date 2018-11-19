#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/event.h>
#include <arpa/inet.h>

#include <strings.h>
#include <unistd.h>

#define backlog 10
#define portnumber 8080
#define maxlength 100

void Bind(int socket) {

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htonl(portnumber);

    if (bind(socket, (struct sockaddr *) &server, sizeof(server)) == -1);
    {
        printf("error while binding socket");
        exit(1);
    }

}

void Listen(int socket) {
    listen(socket, backlog);
    if (listen(socket, backlog) == -1) {
        printf("error while listening for socket");
        exit(1);
    }
}

int main() {
    int listening_socket;
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);

    Bind(listening_socket);
    Listen(listening_socket);

    while (1) {
        ssize_t client_size;
        struct sockaddr_in client;
        client_size = sizeof(client);
        int client_socket;
        client_socket = accept(listening_socket, (struct sockaddr *) &client, &client_size);

        char message[maxlength + 1];

    }


    return 0;
}