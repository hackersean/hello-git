#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include"unistd.h"
using namespace std;
int main()
{
   char cmmd[2]; 
   FILE *file=fopen("in.txt","r");
   do
   {
      char str[1010];
      char ch;
      if(file==0)  exit(1);
      while( (ch=getc(file))!=EOF )
      {
        printf("%c",ch);
      }
      if(fseek(file,0,SEEK_SET)==-1) perror("fail");
   }while(gets(cmmd),cmmd[0]!='q');
   fclose(file);
   return 0;
}
