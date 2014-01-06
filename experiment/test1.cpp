#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int main()
{
    FILE *file=fopen("in.txt","r");
    char str[1010];
   char ch;
    if(file==0)  exit(1);
    while(ch=getc(file))
    {
       printf("%s\n",ch);
    }
    puts("");
    return 0;
}
