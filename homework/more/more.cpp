#include<iostream>
#include"stdlib.h"
#include"stdio.h"
using namespace std;
void do_more(FILE *);
int see_more(FILE *);
int main(int ac,char *av[])
{
//	 cout<<ac<<endl;
	 FILE *fp;
	 if(ac==1)
	 {
	      do_more(stdin);
	 }
	 else
	 {
	      for(int i=1;i<ac;i++)
	      {
			    if((fp=fopen(av[i],"r"))!=NULL) 
		        {
					   do_more(fp);
					   fclose(fp);
			    }
			    else exit(1);
		  }     	
	 }
	 return 0;
}
void do_more(FILE *fp)
{
      char str[513];
      int replay;
      int js=0; 
      FILE *fp_tty=fopen("/dev/tty","r");
      if(fp_tty==NULL) exit(1);
      while(fgets(str,512,fp))
      {
		     if(js==24)
		     {
				   replay=see_more(fp_tty);
				   if(replay==0) break;
				   js-=replay;
		     }
		     if(fputs(str,stdout)==EOF)
		     {
				 exit(1);
		     }
		     js++;
      }
}
int see_more(FILE *fp)
{
      printf("\033[7m more? \033[m");
      
      char c;
      while((c=getc(fp))!=EOF)
      {
		   if(c=='q') return 0;
		   else if(c==' ') return 24;
		   else if(c=='\n') return 1;
	  }
	  return 0;
}
