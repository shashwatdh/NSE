#include<stdio.h>
#include<errno.h>
void main(int argc,char *argv[])
{
    char err[100];
    if(argc!=3)
       printf("\n invalid request");
    else
    {
       if(rename(argv[1],argv[2])!=-1)
       {
	   	   printf("\n successful");
       }
       else
       {
			   printf("\n error in renaming file");
			   perror(err);
       }  	
    }  
}
