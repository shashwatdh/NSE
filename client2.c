#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <error.h>
#include "atof_ci.h"
#define PORT 1500
int sockfd;

void myerror(char *msg)
{
    perror(msg);
    exit(0);
}

void terminate()
{
   	char str[20]="terminating";
   	char buf[6]="close";
	if (write(sockfd, buf, sizeof(buf)) < 0)
	{
		printf("\nERROR writing to socket");
		exit(EXIT_FAILURE);
	}
	close(sockfd);
	
	write(1,str,strlen(str));
	exit(EXIT_SUCCESS);
}
void main()
{
	int n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	int m=0,wait,id;
	int pid,status,size;
	double principal,rate,limit=(pow(2,8*sizeof(unsigned int))-1);
	float yrs;
	unsigned int count=0;
	double buf[4];
	char str[1000],tmp[100];
	size=sizeof(buf)/sizeof(buf[0]);
	signal(SIGINT, terminate);
	//printf("sizeof buf array:%d,start addr:%u",sizeof(buf),buf);
	//printf("%f",pow(2,8*sizeof(unsigned int))-1);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        myerror("ERROR opening socket");
    server = gethostbyname("ubuntu");
    if (server == NULL) {
        printf("ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(PORT);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        myerror("ERROR connecting");
	while(!feof(stdin))
	{
		printf("\n Enter i/p:");
		gets(str);
		if((status=atofci(str,buf,size))>0)
		{
			
			if(write(sockfd,str,sizeof(str))<0)
			{
				myerror("ERROR writing to socket");
			}
			read(sockfd,tmp,sizeof(tmp));
            printf("\nci:%lf",atof(tmp));
			
		}
		else
		{
			if(status==-1)
			{
				printf("\n characters other than 0-9 and '.' aren't allowed!");
			}
			else if(status==-2)
			{
				printf("\n array passed as argument doesn't has sufficient space");
			}
			else if(status==-3)
			{
				printf("\n principal,rate and time values should be >0");
			}
			else if(status==-4)
			{
				printf("\n out of bound error!");
			}
			else if(status==-5)
			{
				printf("\n only 4 i/p are required!");
			}
		}	
		
		//4294967295
	}
	strcpy(str,"close");
	if(write(sockfd,str,sizeof(str))<0)
		{
			myerror("ERROR writing to socket");
		}
	printf("\n terminating ..");
	close(sockfd);
}