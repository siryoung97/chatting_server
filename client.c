#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define buffersize 100

void *receive_message(void *arg);

void *send_message(void *arg);

int main() {
    int sock;
    struct sockaddr_in server_address;
    pthread_t send_thread, receive_thread;

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = htonl(8080);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));

    pthread_create(&send_thread, NULL,send_message, (void *) sock);
    pthread_create(&receive_thread, NULL,receive_message, (void *) sock);
    close(sock);
    return 0;
}

void *send_message(void *arg) {
    int sock = *((int *)arg);
    char message[buffersize];
    while (1){
        fgets(message,buffersize,stdin);
        if(!strcmp(message,"q\n")||strcmp(message,"q\n"))
        {
            close(sock);
            exit(0);
        }
        write(sock,message,strlen(message));
    }
    return NULL;
}

void *receive_message(void *arg) {
    int sock = *((int *)arg);
    char message[buffersize];
    int str_len;
    while (1){
        str_len=read(sock,message, sizeof(message)-1);
        message[str_len]=0;
        fputs(message,stdout);
    }
    return NULL;
}