#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>
#include<errno.h>
#define MAX 100
void main(int argc,char *argv[])
{
   char *source,*dest,*fname;
   char f_buf[MAX];
   int s_len,i,flag=0;
   struct stat buf,buf1; 
   uid_t id=getuid();
   FILE *fp,*fp1;
   if(argc==3)
   {
     	source=argv[1];
     	dest=(char*)malloc(strlen(argv[2])*(sizeof(char)));//argv[2];
     	strcpy(dest,argv[2]);
     	printf("dest=%s",dest);
     	if(lstat(source,&buf)!=-1)
     	{
     	   if(S_ISREG(buf.st_mode))
			{
				if(lstat(dest,&buf1)!=-1)
				{
					if(S_ISDIR(buf1.st_mode))
					{
						if((buf1.st_uid==id && (buf1.st_mode & S_IWUSR) && (buf1.st_mode & S_IXUSR))||((buf1.st_mode & S_IWOTH) && (buf1.st_mode & S_IXOTH)))
						{
							printf("\nuid mathed-%d,dest folder=%s",id,argv[2]);
							//if correct arguments are entered, fetch filename from source
							s_len=strlen(source);
							for(i=s_len-1;i>=0;i--)
							{
								if(source[i]=='/' && i!=s_len-1)
								{
									flag=1;
									break;
								}
							}
							if(!flag)
								fname=source;
							else
								fname=source+i+1;
							printf("\nfile:%s",source);
							dest=(char *)realloc(dest,(strlen(dest)+strlen(fname)+1));
							strcat(dest,"/");
							strcat(dest,fname);
							printf("\ndest:%s",dest);
							if(strcpy(argv[2],".") && (lstat(dest,&buf1)==0))
							{
								printf("\n file already exists");
								exit(EXIT_SUCCESS);

							}
							
							if((fp=fopen(source,"r"))!=NULL && (fp1=fopen(dest,"w"))!=NULL)
							{
								printf("\n opened both files");
								while(!feof(fp))
	  			            	{
	  			           	    	if(fgets(f_buf,MAX,fp)!=NULL)
	  			           	    	{
	  			           	  	 		if(fputs(f_buf,fp1)==EOF)
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
							//after copying delete source file
							if(remove(source)==0)
							{
								printf("\nsucessfully moved!");
							}
							else
						  		printf("\n error deleting file");
							
						}
						else
					   		printf("\npermission constraints violated");
					}
					else
					   printf("\n invalid arguments");
				}
				else
				{
					printf("\n invalid file!");
					perror("error");	
				}  
			}
			else
			   printf("\n invalid arguments [file][folder]");	
		}
		else
			printf("\n invalid file name:%s",argv[1]);
   }	
}
