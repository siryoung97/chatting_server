#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>

#define buffersize 100
#define MAXCLIENT 256
char message[buffersize];
int client_socks[MAXCLIENT];
int client_count = 0;

void *handle_client(void *arg);

void *sendmessage(char *message, int len);

void *receivemessage(void *message);

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_address, client_address;
    int client_address_size;
    pthread_t thread_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8080);
    while (1) {
        client_address_size = sizeof(client_address);
        client_sock = accept(server_sock, (struct sockaddr_in *) &server_address, sizeof(server_address));
        client_socks[client_count++] = client_sock;
        pthread_create(&thread_address, NULL, handle_client, (void *) &client_sock);
        pthread_detach(thread_address);
    }

}

void *handle_client(void *arg) {
    int sock = *((int *) arg);
    while ((read(sock, message, sizeof(message))) != 0)
        sendmessage(message, strlen(message));
    return NULL;

}

void *sendmessage(char *message, int length) {
    int i;
    for (i = 0; i < client_count; i++)
        write(client_socks[i], message, length);
}


