#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"fcntl.h"
#include"unistd.h"
#include"utmp.h"
#include"time.h"
using namespace std;
void show_info(utmp*);
int main()
{
    utmp current_record;
    int utmpfd;
    int reclen=sizeof(current_record);
    if((utmpfd=open(UTMP_FILE,O_RDONLY)) == -1)
    { 
		 perror(UTMP_FILE);
		 exit(1);
    }
    while(read(utmpfd,&current_record,reclen)==reclen)
    {
		  show_info(&current_record);
    }
    close(utmpfd); 
	return 0;
}
char* showtime(long x)
{
	   char *cp;
	   cp=ctime(&x);
	   return cp;
}
void show_info(utmp *fp)
{
	 if(fp->ut_type != USER_PROCESS) return;
	 printf("%s  %s ",fp->ut_user,fp->ut_line);
	 printf("%.12s",showtime(fp->ut_time)+4);
	 printf(" (%s)",fp->ut_host);
     cout<<endl;
     return;
}
