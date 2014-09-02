/*
         server 服务端
*/
#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <string.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
using namespace std;
#define MAXLINE 80 
#define SERV_PORT 8888 

inline void oops(string str)         //出错
{
    perror(str.c_str());
    exit(EXIT_FAILURE);
}

void init(int sockfd)
{
    sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET;                    //协议设置
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);     //绑定本地
	servaddr.sin_port = htons(SERV_PORT);              //绑定端口
	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)         //本地结构体用于bind
			oops("bind error");  
}



void do_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen) 
{ 
	int n; 
	socklen_t len; 
	char mesg[MAXLINE]; 
	for(;;) 
	{ 
		    memset(mesg,0,sizeof mesg);
			len = clilen;                 //源地址长度
			n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len); 
			sendto(sockfd, mesg, n, 0, pcliaddr, len); 
			cout<<"from remote:"<<mesg;
	} 
} 
int main(void) 
{ 
	
	int sockfd=socket(AF_INET, SOCK_DGRAM, 0); 
	init(sockfd);
	sockaddr_in cliaddr;
	cout<<"service start:"<<endl;
	do_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)); 
	return 0; 
}
