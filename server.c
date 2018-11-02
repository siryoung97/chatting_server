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
    int n;
    char message[1001];
    struct sockaddr_in serveraddress;
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
    listen(listenfd, 1024);
    for(;;){
        connfd = accept(listenfd, (struct sockaddr *) &serveraddress, NULL);
        read(connfd,message,strlen(message));
        printf("%s", message);
    }



    return 0;
}