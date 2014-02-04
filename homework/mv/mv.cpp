#include<iostream>
#include"unistd.h"
#include "stdlib.h"
#include<cstdio>
using namespace std;
int main(int av,char *ac[])
{
   if(av!=3 || access(ac[1],F_OK)==-1)
   {
      cerr<<"argument faild"<<endl;
      exit(1);
   }
   rename(ac[1],ac[2]);
   return 0;
}
