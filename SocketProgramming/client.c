#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
    int clnt_sock;
    struct sockaddr_in serv_addr;
    char message[1024] = {0x00, };

    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(clnt_sock = -1)
        error_handling("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
}