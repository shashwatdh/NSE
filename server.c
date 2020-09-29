#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "calc.h"
#define PORT 1500
void calc_ci(int);
int main()
{
	int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in server_addr, client_addr;
    int pid;
	//setup socket for comm.
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
    {
    	printf("ERROR opening socket");
    	exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *) &server_addr,sizeof(server_addr)) < 0) 
    {
    	printf("ERROR on binding");
    	exit(1);
    }
    listen(sockfd,5);
    clilen = sizeof(client_addr);
    while(1)
    {
    	newsockfd = accept(sockfd,(struct sockaddr *) &client_addr, &clilen);
    	if(newsockfd)
    	{
    		pid=fork();
    		if(pid<0)
    		{
    			printf("\n fork error!");
    			exit(1);
    		}
    		else
    		{
    			if(!pid)
    			{
    				printf("computing for client:%d\n",client_addr.sin_port);
    				calc_ci(newsockfd);
         			close(newsockfd);
         			exit(0);
    			}
    		}
    		signal(SIGCHLD,SIG_IGN);
    	}
    }          
	return 0;
}

void calc_ci(int sock)
{
	int flag=0,n;
	double buf[4],princ,rate,tmp[1];
	float yrs;
	while(!flag)
	{
		n=read(sock,buf,sizeof(buf));
		if(n)
		{
			if(!(flag=(int)buf[3]))
			{
				princ=buf[0];
				rate=buf[1];
				yrs=(float)buf[2];
				printf("\n %lf",princ);
				tmp[0]=ci(princ,rate,yrs);
				write(sock,tmp,sizeof(tmp));
			}
			else
				printf("\n process terminating...");
		}
		else
		{
			flag=1;
		}
	}
}
