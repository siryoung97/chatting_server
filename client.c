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
    struct sockaddr_in clientaddress;
    char message[1001];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("socket error");
        exit(1);
    }
    bzero(&clientaddress, sizeof(clientaddress));
    clientaddress.sin_family = AF_INET;
    clientaddress.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &clientaddress.sin_addr);
    cfd = connect(sockfd, (struct sockaddr *) &clientaddress, sizeof(struct sockaddr_in));
    gets(message);
    write(cfd,message,strlen(message));


    return 0;
}