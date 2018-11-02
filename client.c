#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

/*void str_cli(FILE *fp, int sockfd) {
    char sendmessage[1001];
    while (fgets(sendmessage, strlen(sendmessage), fp) != NULL)
        write(sockfd, sendmessage, strlen(sendmessage));


}*/

int main() {
    int sockfd;
    int cfd;
    struct sockaddr_in serveraddress;
    char message[]="Hello World";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("socket error");
        exit(1);
    }
    bzero(&serveraddress, sizeof(serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(8080);
    serveraddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    inet_pton(AF_INET, "127.0.0.1", &serveraddress.sin_addr);
    cfd = connect(sockfd, (struct sockaddr *) &serveraddress, sizeof(struct sockaddr_in));
    write(cfd,message,strlen(message));


    return 0;
}