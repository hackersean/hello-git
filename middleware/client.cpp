/*
         client 客户端

*/
#include <iostream>
#include <sys/types.h> 
#include <fcntl.h>
#include <sys/socket.h> 
#include <string.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
using namespace std;
#define MAXLINE 256          //缓冲区大小
#define SERV_PORT 8888 
#define CONFIG "config"


inline void oops(string str)         //出错
{
    perror(str.c_str());
    exit(EXIT_FAILURE);
}

sockaddr_in init()                  //初始化信息
{
	//读取ip地址
	char ip[20];
	FILE *file=fopen(CONFIG,"r");
    if(file==NULL)
    {
	   oops("配置文件打开失败");
    }
    else
    {
	   fscanf(file,"%s",ip);
    }
    fclose(file);  
	
	//读取
	
	sockaddr_in servaddr;            //声明socket地址信息结构体
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(SERV_PORT);  
	if(inet_pton(AF_INET,ip, &servaddr.sin_addr) <= 0)      //把IP从字符串地址转换成网络地址，写入servaddr
		oops("IPaddress is not a valid\n");
	
	return servaddr;                                        //返回socket
}
void do_cli(int sockfd, sockaddr *pservaddr, socklen_t servlen) 
{
	int n; 
	char sendline[MAXLINE], recvline[MAXLINE + 1];                             //发送和接收的缓冲区
	if(connect(sockfd, (struct sockaddr *)pservaddr, servlen) == -1)           //建立连接
	{ 
			oops("connect error");  
	} 
	sendline[0]='g';   
	write(sockfd, sendline, 1);   
	while(true) 
	{  
//			write(sockfd, sendline, 1);
             cout<<"ok"<<endl;
			n = recv(sockfd, recvline, MAXLINE, 0);
			if(n == -1)  
			    oops("read error"); 
			else if(recvline[0]=='o')
				return;
		    cout<<recvline<<endl;
			//fwrite(recvline,n,1,stdout);
//			cout<<"from serve:"<<recvline; 
	} 
} 
int main(int argc, char **argv) 
{ 
	sockaddr_in servaddr=init();            //初始化信息
	int sockfd=socket(AF_INET, SOCK_DGRAM, 0);            //用于保存socket文件描述符
//	cout<<"client start:  sss"<<endl;
	do_cli(sockfd, (sockaddr*) &servaddr, sizeof(servaddr));      //发送执行函数
	return 0; 
}
