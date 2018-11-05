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
    int serv_sock;
    int client_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    socklen_t clnt_addr_size;


    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);
    bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(serv_sock, 1024);
    clnt_addr_size = sizeof(cli_addr);
    client_sock = accept(serv_sock, (struct sockaddr *) &cli_addr, &clnt_addr_size);
    for (;;) {
        str_read(stdout, client_sock);

    }

}