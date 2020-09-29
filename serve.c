#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include "calc.h"
void main()
{
	int m=0,wait,id;
	pid_t pid;
	double principal,rate;
	float yrs;
	unsigned int count=0;
	//printf("%f",pow(2,8*sizeof(unsigned int))-1);
    
	while(!feof(stdin))
	{
		
		scanf("%d %lf %lf %f",&id,&principal,&rate,&yrs);
		if(principal>0 && rate >0 && yrs>0 && id<= (pow(2,8*sizeof(unsigned int))-1))
		{
			pid=fork();
			if(pid<0)
				printf("\n fork() failed");
			else
			{
				if(!pid)
				{
					printf("\nfor id:%u; principal:%lf, rate:%lf, time:%f",id,principal,rate,yrs);
					printf("\nCompound Interest:%lf",ci(principal,rate,yrs));
					exit(EXIT_SUCCESS);
				}
				
			
			}
			signal(SIGCHLD,SIG_IGN);	
		}
		else
			printf("principal,rate and time values should be >0 and id <= %.0f",pow(2,8*sizeof(unsigned int))-1);
		
		//4294967295
	}
}