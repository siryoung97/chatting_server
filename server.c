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

void read_message(int socket) {
    char message[maxlength + 1];
    read(socket, message, sizeof(message) - 1);
    fputs(message,stdout);
}

void Bind_Socket(int socket) {

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portnumber);

    if (bind(socket, (struct sockaddr *) &server, sizeof(server)) == -1) {
        perror("Error Binding Socket");
        exit(1);
    }

}

void Listen_For_Socket(int socket) {
    listen(socket, backlog);
    if (listen(socket, backlog) == -1) {
        perror("Error While Listening For Socket");
        exit(1);
    }
}

int main() {
    int listening_socket;
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);

    Bind_Socket(listening_socket);
    Listen_For_Socket(listening_socket);

    while (1) {
        unsigned int client_size;
        struct sockaddr_in client;
        client_size = sizeof(client);
        int client_socket;
        client_socket = accept(listening_socket, (struct sockaddr *) &client, &client_size);
        read_message(client_socket);
    }


    return 0;
}