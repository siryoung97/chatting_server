#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef int fd;
#define maxlength 100

void sendmessage(int sock){
    char message[maxlength + 1];
    fputs(message,stdin);
    write(sock,message, sizeof(message));
}
int main() {
    fd sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    connect(sock, (struct sockaddr *) &server, sizeof(server));

    while (1) {
        sendmessage(sock);
    }

    return 0;
}