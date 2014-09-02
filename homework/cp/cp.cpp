#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"unistd.h"
#include"fcntl.h"
#define BUFFERSIZE 100000
#define COPYMODE 0644
using namespace std;
char buf[BUFFERSIZE];
void oop(char *,char *);
int main(int ac,char *av[])
{
	int in_fd,out_fd,n_chars;
	if(ac!=3)
	{
		fprintf(stderr,"usage: %s source destination\n",*av);
		exit(1);
    }
    if((in_fd=open(av[1],O_RDONLY)) == -1)
    {
		 oop("cannot open",av[1]);
	}
	if((out_fd=creat(av[2],COPYMODE)) == -1)
	{
		 oop("cannot open",av[2]);
	}
	while((n_chars = read(in_fd,buf,BUFFERSIZE)) > 0)
	{
		    if( write(out_fd,buf,n_chars) != n_chars )
		    {
		         oop("Write error to",av[2]);
		    }
        }
    if( n_chars == -1 ) oop("Read error from",av[1]);
    if( close(in_fd)==-1 || close(out_fd)==-1) oop("Error close files","");
	return 0;
}
void oop(char *str1,char *str2)
{
        fprintf(stderr,"Error: %s\n",str1);
        perror(str2);
        exit(1);
}

