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
    int sock;
    struct sockaddr_in serv_addr;
    char message[101];
    gets(message);
    int str_len;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8080);
    connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    for (;;) {
        write(sock, message, sizeof(message));
    }
}