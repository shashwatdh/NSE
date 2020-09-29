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
	  		    	//Other option can be anything
	  		    	//either user can give path of a file or a directory
	  		    	//if file path is given again 3 possiblities are there
	  		    	//1) file exits
	  		    	//2) file doesn't exist
	  		    	//3) dir in path doesn't exist
	  		    	//if folder path is given we have to print error msg
	  				/*if(lstat(argv[2],&finf1)!=-1)
	  				{		
	  					if(S_ISREG(finf1.st_mode))
	  					{*/
	  				strcpy(folder,argv[2]);
	  				if((dir=opendir(folder))!=NULL)
	  				{
	  					printf("\n second srgument must be file and not a folder!");
	  				}
	  				else
	  				{
	  					// either wrong filename or wrong folder was entered as 2nd srg
	  					// or correct file path was entered
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
	  						// either 2nd arg was filename, or file may or may not exist
	  						fp=fopen(argv[1],"r");
	  			            if((fp1=fopen(argv[2],"w"))!=NULL)
	  			            {
	  			            	while(!feof(fp))
	  			            	{
	  			           	    	if(fgets(buf,MAX,fp)!=NULL)
	  			           	    	{
	  			           	  	    	if(fputs(buf,fp1)==EOF)
							       		{
							  	      		printf("\n error writing the file!");
	  			           	  	      		break;
							       		}
							   		}
							  
								}
								printf("\n finished rw");
								fclose(fp);
	    						fclose(fp1);
	  			            }
	  			            else
	  			            {
	  			            	printf("\n error opening file in write mode");
	  			            }
	  					}
	  				}
	  			            /*fp=fopen(argv[1],"r");
	  			            if((fp1=fopen(argv[2],"w"))!=NULL)
	  			            {
	  			            	while(!feof(fp))
	  			            	{
	  			           	    	if(fgets(buf,MAX,fp)!=NULL)
	  			           	    	{
	  			           	  	    	if(fputs(buf,fp1)==EOF)
							       		{
							  	      		printf("\n error writing the file!");
	  			           	  	      		break;
							       		}
							   		}
							  
								}
								printf("\n finished rw");
								fclose(fp);
	    						fclose(fp1);
	  			            }
	  			            else
	  			            {
	  			            	printf("\n cp: cannot create regular file '%s': No such file or directory",argv[2]);
	  			            }*/
			  			/*}
			  			else
			  			{
			  				printf("\nonly can be copied!'");
			  			}
		  			}*/
		  			
			    }
			    else
		  			printf("\n cant copy same files");
			  }
			  else
			  {
			   	printf("\nonly files can be copied!'");
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
