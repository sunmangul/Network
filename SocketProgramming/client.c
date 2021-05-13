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

    // IPv4, TCP연결지향형 소켓 생성
    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(clnt_sock == -1)
        error_handling("socket error");

    // 인자로 받은 서버 주소 정보를 저장
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;                   // 서버주소체계 : IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 서버주소 IP저장
    serv_addr.sin_port = htons(atoi(argv[2]));      // 서버주소 프트번호 저장

    // 클라이언트 소켓부분에 서버 연결
    if(connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect error");
    // 연결이 되면 데이터 받음
    if(read(clnt_sock, message, sizeof(message)-1)==-1)
        error_handling("read error");
    printf("Message from server : %s\n", message);

    // 통신이 끝났기 때문에 소켓 닫기
    close(clnt_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}