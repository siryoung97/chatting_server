#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
int maxbuffer =101;
int main(){
    int sock;
    struct sockaddr_in server_address;
    char message[maxbuffer];
    sock=socket(AF_INET,SOCK_STREAM,0);
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(8080);
    server_address.sin_addr.s_addr=htonl(INADDR_ANY);
    connect(sock,(struct sockaddr *)&server_address, sizeof(server_address));


    return 0;
}