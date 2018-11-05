#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>


void str_read(FILE *fp, int sockfd) {
    char message[1001];
    if (read(sockfd, message, sizeof(message)) < 0) {
        printf("Server Error");
        exit(1);
    }
    read(sockfd, message, sizeof(message) - 1);
    fputs(message, fp);
    /*printf("From Client: %s", message);*/
}

int main() {
    char message[101];
    int server_sock, client_sock;

    struct sockaddr_in server_address, client_address;
    socklen_t client_address_size;


    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8080);
    bind(server_sock, (struct sockaddr *) &server_address, sizeof(server_address));
    listen(server_sock, 1024);
    client_address_size = sizeof(client_address);
    client_sock = accept(server_sock, (struct sockaddr *) &client_address, &client_address_size);
    for (;;) {
        str_read(stdout, client_sock);

    }

}