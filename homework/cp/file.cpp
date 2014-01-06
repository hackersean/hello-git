#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "unistd.h"
#include "fcntl.h"
#include "utmp.h"
#include <cstring>
#define BFLE /home/sean/github/test/cp/utmp
using namespace std;
int log(char *);
int main(int ac,char *av[])
{
    if(ac!=2)
    {
        fprintf(stderr,"fail");
        exit(1);
    }
    log(av[1]);
    return 0;
}
int log(char *line)
{
    int fd;
    if((fd=open("utmp",O_RDWR)) == -1)
    {
        perror("cannot open file\n");
        exit(1);
    }
    utmp rec[1024];
    utmp temp;
    int rec_len=sizeof(rec);
    int temp_len=sizeof(temp);
    int bitlen=0;
    int ps=-1;
    while((bitlen=read(fd,&rec,rec_len))>0)
    {
        int flag=0;
        int num=bitlen/temp_len;
        printf("%d\n",num);
	for(int i=0;i<num;i++)
        {
            if(strcmp(rec[i].ut_line,line)==0)
            {
                flag=1;
                rec[i].ut_name[0]='h';
                rec[i].ut_type = DEAD_PROCESS;
//                if(time(&rec[i].ut_time!=-1)
                {
                    if(lseek(fd,-(num-i)*temp_len,SEEK_CUR)!=-1)
                    {
                        if(write(fd,&rec[i],temp_len)==temp_len)
                        {
                               flag=1;
                        }
                    }
                }
                break;
	    }
//            printf("%s\n",rec[i].ut_name);
             
        }
        if(flag=1) break;
    }
    if(bitlen==-1)
    {
       perror("file read error\n");
       exit(1);
    }
    close(fd);
    return 0;
}
