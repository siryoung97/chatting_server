#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

/*void str_read(int sockfd) {
        int n;
        char message[1001];
        read(sockfd,message,strlen(message));
        printf("From Client: %s",message);
}*/

int main() {
    int listenfd, connfd;
    char message[1001];
    struct sockaddr_in serveraddress;
    struct sockaddr_in clientaddress;
    socklen_t clientaddress_size;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        printf("socket error");
        exit(1);
    }
    bzero(&serveraddress, sizeof(serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(8080);
    bind(listenfd, (struct sockaddr *) &serveraddress, sizeof(serveraddress));
    clientaddress_size = sizeof(clientaddress);
    listen(listenfd, 1024);
    connfd = accept(listenfd, (struct sockaddr *) &clientaddress, &clientaddress_size);
    read(connfd, message, strlen(message) - 1);
    printf("Message Received: %s", message);


    return 0;
}