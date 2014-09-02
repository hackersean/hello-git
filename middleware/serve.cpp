/*
         server ·þÎñ¶Ë
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

inline void oops(string str)         //³ö´í
{
    perror(str.c_str());
    exit(EXIT_FAILURE);
}

void do_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen) 
{ 
	int n; 
	socklen_t len; 
	char mesg[MAXLINE]; 
	for(;;) 
	{ 
		    memset(mesg,0,sizeof mesg);
			len = clilen; 
			n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len); 
			sendto(sockfd, mesg, n, 0, pcliaddr, len); 
			cout<<"from remote:"<<mesg;
	} 
} 
int main(void) 
{ 
	int sockfd; 
	struct sockaddr_in servaddr, cliaddr; 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(SERV_PORT); 
	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) 
	{ 
			oops("bind error");  
	} 
	cout<<"service start:"<<endl;
	do_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)); 
	return 0; 
}
