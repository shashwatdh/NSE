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
#include <error.h>
#define PORT 1500
void myerror(char *msg)
{
    perror(msg);
    exit(0);
}

void main()
{
	int sockfd,n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	int m=0,wait,id;
	int pid;
	double principal,rate,tmp[1],limit=(pow(2,8*sizeof(unsigned int))-1);
	float yrs;
	unsigned int count=0;
	double buf[4];
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
		
		scanf("%d %lf %lf %f",&id,&principal,&rate,&yrs);
		if(principal>0 && rate >0 && yrs>0 && (id<=limit && id>=0) )
		{
			buf[0]=principal;
			buf[1]=rate;
			buf[2]=yrs;
			buf[3]=0;
			if(write(sockfd,buf,sizeof(buf))<0)
			{
				myerror("ERROR writing to socket");
			}
			read(sockfd,tmp,sizeof(tmp));
            printf("\nci:%lf",tmp[0]);
			
		}
		else
			printf("principal,rate and time values should be >0 and id <= %.0f",limit);
		
		//4294967295
	}
	buf[0]=-1;
	buf[1]=-1;
	buf[2]=-1;
	buf[3]=1; //flag
	if(write(sockfd,buf,sizeof(buf))<0)
		{
			myerror("ERROR writing to socket");
		}
	printf("\n terminating ..");
	close(sockfd);
}