#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include"unistd.h"
using namespace std;
int main()
{
   string str; 
   FILE *file=fopen("in.txt","w");
   while(getline(cin,str),str[0]!='q')
   {
       fwrite(str.c_str(),str.size(),1,file);
   }
  // fclose(file);
   return 0;
}
