#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#define MAX 100
#define CHAR_MAX 255
void main(int argc,char *argv[])
{
	char buf[MAX],folder[CHAR_MAX];
	struct stat finf,finf1;
	DIR *dir;
	FILE *fp,*fp1;
	int len,i,flag=0;
	if(argc==3)
	{
	  	if(lstat(argv[1],&finf)!=-1)
	  	{
	  		if(S_ISREG(finf.st_mode))
	  		{
	  			if(strcmp(argv[1],argv[2])!=0)
	  			{
	  				strcpy(folder,argv[2]);
	  				if((dir=opendir(folder))!=NULL)
	  				{
	  					printf("\n second srgument must be file and not a folder!");
	  				}
	  				else
	  				{
	  					len=strlen(folder);
	  					for(i=len-1;i>=0;i--)
	  					{
	  						if(folder[i]=='/')
	  						{
	  							folder[i]='\0';
	  							flag=1;
	  							break;
	  						}
	  					}
	  					if(flag)
	  					{
	  						//folder is present in path
	  						if((dir=opendir(folder))==NULL)
	  						{
	  							printf("\n cp: cannot create regular file '%s': No such file or directory",argv[2]);
	  						}
	  						else
	  						{
	  							//file may or may not exists
	  							flag=0;
	  						}
	  					}
	  					if(!flag)
	  					{
	  						fp=fopen(argv[1],"r");
	  			        	if((fp1=fopen(argv[2],"w"))!=NULL)
	  			        	{
	  			        		while(!feof(fp))
	  			            	{
	  			           	    	if(fread(buf,sizeof(char),MAX,fp)<MAX &&(!feof(fp)))
	  			           	    	{
	  			           	  	    	printf("\n error reading the file!");
	  			           	  	    	break;
							    	}
							    	if(fwrite(buf,sizeof(char),MAX,fp1)<MAX)
							    	{
							  	    	printf("\n error writing the file!");
	  			           	  	    	break;
							    	}
								}
								printf("\n finished rw");
								fclose(fp);
	                        	fclose(fp1);
	  			        	}
	  					}
	  				}
	  				
	  			}
	  			else
		  			printf("\n cant copy same files");
	  					
			}
			else
			{
				printf("\nonly regular files can be copied!'");
			}
		}
		else
		{
			printf("\n file '%s' doesn't exist",argv[1]);
		}
	}
	else
	    printf("\n invalid command");
	    
}
