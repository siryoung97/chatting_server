#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

int client_max = 100;
int client_count = 0;

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_address, client_address;
    unsigned int client_address_size;
    int pid;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8080);
    client_address_size = sizeof(client_address);
    bind(server_sock, (struct sockaddr *) &server_address, sizeof(server_address));
    listen(server_sock, client_max);
    for (;;) {
        client_sock = accept(server_sock, (struct sockaddr *) &server_address, &client_address_size);
        client_count++;
        if ((pid = fork()) == 0) {
            if (client_sock != 0) {
                printf("%d", client_count);

            }
            close(client_sock);
            exit(0);
        }
        close(client_sock);
    }

    return 0;
}
