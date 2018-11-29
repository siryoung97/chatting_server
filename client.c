#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#define maxlength 100
typedef int fd;

void sendmessage(int sock) {
    char message[maxlength + 1];
    fgets(message, sizeof(message), stdin);
    write(sock, message, sizeof(message));
}

void set_connect_socket(fd sock) {
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    connect(sock, (struct sockaddr *) &server, sizeof(server));
}

int main() {
    fd sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    while (1) {
        set_connect_socket(sock);
        sendmessage(sock);
    }

    return 0;
}