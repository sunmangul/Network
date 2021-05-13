#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
    int serv_sock;
    int clnt_sock;

    // sockaddr_in = 소켓 주소의 틀을 형성해주는 구조체(AF_INET일 경우 사용)
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;  //accept함수에서 사용
    socklen_t clnt_addr_size;

    // IPv4, TCP연결, default(앞에서 형식 지정이 됨)
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
    {
        error_handling("socket error");
    }

    // 메모리 초기화, IP주소와 포트 지정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;                   // IPv4
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);    // ip주소
    serv_addr.sin_port=htons(atoi(argv[1]));        // port

    // 소켓, 서버주소 바인딩
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
    {
        error_handling("bind error");
    }

    // 연결 대기열 크기 지정(생성)
    if(listen(serv_sock, 5)==-1)        // 연결 대기열 5개 생성
    {
        error_handling("listen error");
    }

    // 클라이언트로의 요청 수락
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1)
    {
        error_handling("accept error");
    }

    // 데이터 전송
    char msg[]  = "Hello this is server!\n";
    write(clnt_sock, msg, sizeof(msg));

    //소켓 닫기
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}