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
#define LL long long
#define BUFFER 250
#define MAXLINE 80 
#define SERV_PORT 8888 
#define TCP_PORT 7777
#define DATA_PATH  "/data/data"



inline void oops(string str);

struct NODE
{
	 static LL num;
	 int ps;
     char str[BUFFER];
	 char ans[BUFFER];
     void play()
	{
		ps=0;
		int len(strlen(str));
        sprintf(ans,"%lld",num);
        while(ans[ps]!=0)
		{
			++ps;
		}
//		                  cout<<"ok:   "<<num<<" "<<ans<<" "<<len<<" "<<ps<<endl;
		int tp=len-2;
        int t=tp/3;
		int w=t*2;
//       cout<<t<<" "<<w<<endl;
		for(int i=tp-1;i>=w;--i,++ps)
		{
            ans[ps]=str[i];
		}
		for(int i=t-1;i>=0;--i,++ps)
		{
			ans[ps]=str[i];
		}

		ans[ps]='\r';
		ans[++ps]='\n';
		ans[++ps]=0;
		++ps;
//		cout<<"ko: "<<ps<<endl;
//		cout<<ans;
		++num;
	}
};
LL NODE::num(0);

struct DATA
{
	FILE* fp;                  //注意
	DATA()
	{
		if((fp=fopen(DATA_PATH,"r"))!=NULL)
		{
			
		}
		else
		{
			oops("数据文件打开失败");
		}
    }
	


    
}data;

void read_data(DATA &data)
{
	NODE temp;
    if(fgets(temp.str,BUFFER,data.fp)!=NULL)
	{
	      temp.play();
	}

}

inline void oops(string str)         //出错
{
    perror(str.c_str());
    exit(EXIT_FAILURE);
}

void init_udp(int sockfd)
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
	NODE temp;
	for(;;) 
	{ 
		    memset(mesg,0,sizeof mesg);
			len = clilen;                                                             //源地址长度
			n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len); 
//			sendto(sockfd, mesg, n, 0, pcliaddr, len); 
//			cout<<"from remote:"<<mesg;

	        if(fgets(temp.str,BUFFER,data.fp)!=NULL)
			{
				temp.play();
                sendto(sockfd,temp.ans,temp.ps,0,pcliaddr,len);
			}
	} 
} 
int main(void) 
{ 
	
//    read_data(data);
	int sockfd(socket(AF_INET, SOCK_DGRAM, 0)); 
	init_udp(sockfd);
	


	sockaddr_in cliaddr;
	cout<<"service start:"<<endl;
	do_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)); 
	return 0; 
}
 