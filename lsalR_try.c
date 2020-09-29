#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<limits.h>
#include<errno.h>
#define MAXFILES 10

struct fname
{
	char name[PATH_MAX];
	struct stat *ptr;
};

struct node
{
   	char path[PATH_MAX];
   	struct node *nxt;
};

struct fname *fptr = NULL;
struct node *head = NULL,*tmp_nxt = NULL;
int maxfiles = MAXFILES;

void ls(char *);

int comparator(const void *p,const void *q)
{
	p = (const char *)p;
	q = (const char *)q;
	return strcmp(p,q);
}

char * procD(char *date)
{
	int i,len,nc=0;
	len = strlen(date);
	for(i=0;i<len;i++)
	{
		if(date[i] == ':' && ++nc == 2)
		{
			date[i] = '\0';
			break;
		}
	}
	return date;
}

void display(int count)
{
	struct passwd *user;
    	struct group  *gr;
	struct node *temp,*t;
	struct stat buf;
    	char *fname;
    	int i,j,flag,f_len;
	for (i = 0;i <= count;i++){
		fname = fptr[i].name;
		flag = 0;
		f_len = strlen(fptr[i].name);
		errno = 0;
		for(j=f_len-1;j>=0;j--)
		{
			if(fname[j] == '/')
			{
				flag = 1;
				break;
			}
		}
		if(flag)
		{
			fname = fname+j+1;
		}
		if(lstat(fptr[i].name,&buf) != -1)
		{   
			if(S_ISDIR(buf.st_mode))
			{
				printf("d");
				if(strcmp(fname,".") != 0 && strcmp(fname,"..") != 0)
				{
					temp = (struct node*)malloc(sizeof(struct node));
					if(!temp)
					{
						printf("\nError allocating memory for creation of node");
						exit(EXIT_FAILURE);
					}
					temp->nxt = NULL;
					strcpy(temp->path,fptr[i].name);
					if(!head)
					{
						head = temp;            	
					}
					else
					{
						t = head;
						while(t->nxt != tmp_nxt)
						{
							t = t->nxt;
						}
						temp->nxt = tmp_nxt;
			 			t->nxt = temp;
					}	
				}
		
			}	
			else if(S_ISLNK(buf.st_mode))
			{	
				printf("l");
			}
			else
			{
				printf("-");
			}
    			printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    			printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    			printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    			printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    			printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    			printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    			printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    			printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    			printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
    			printf( (buf.st_mode & S_ISVTX) ? "t" : "-");
    			printf(" %3lu",buf.st_nlink);
    			user = getpwuid(buf.st_uid);
    			if(user)
			{
				printf(" %15s",user->pw_name);
			}
			else
			{
				printf("\nfor user-%d,value of error:%d\n err msg:%s\n",buf.st_uid,errno,strerror(errno));
			}
			gr = getgrgid(buf.st_gid);
			if(gr)
			{
    	    			printf(" %15s",gr->gr_name);
			}
			else
			{
				printf("\nfor gr-%d,value of error:%d\n err msg:%s\n",buf.st_gid,errno,strerror(errno));
			}
    			printf(" %10ld",buf.st_size);//file size;
       			printf("   %20s",procD(ctime(&buf.st_mtime)));//f[i].ptr->st_mtime);
  			printf(" %s\n",fname);
	
		}  
		else
            	{
                	printf("\n path -%s, doesn't exist",fptr[i].name);
                	exit(EXIT_FAILURE);
            	}

	}
}

int main(int argc,char *argv[])
{
   if(argc == 2)
   {
	DIR *dir;
	errno=0;
	if(!(dir = opendir(argv[1])))
	{
		printf("\nProgram expects directory path");
   		printf("\n error:%d\n err msg:%s\n",errno,strerror(errno));
		exit(EXIT_FAILURE);
	}
	if(closedir(dir) < 0)
	{
		printf("\nUnable to close directory-%s",argv[1]);
		printf("\n error:%d\n err msg:%s\n",errno,strerror(errno));
		exit(EXIT_FAILURE);
	}
	struct node *temp;
	char dir_name[PATH_MAX];
	fptr = (struct fname *)calloc(MAXFILES,sizeof(struct fname));
	if(!fptr)
	{
		printf("\nError allocating memory for array, storing directory's entries' names");
		exit(EXIT_FAILURE);
	}
	if(strlen(argv[1]) >= PATH_MAX)
	{
		printf("\nInput argument too long");
		exit(EXIT_FAILURE);
	}
	strcpy(dir_name,argv[1]);
	ls(dir_name);
	while(head)
	{
		ls(head->path);
		temp = head;
		head = head->nxt;
		free(temp);
	}
	free(fptr);
   }
   else
   	printf("\n invalid argument");
   return 0;
}

void ls(char *arg)
{
	/*
	 * if head is null, then 1st arg should be considered as primary path,
	 * if head points to some addr then tmp must point to nxt node
	 */
	int arg_len = strlen(arg);
	int count = -1;
	DIR *dr;
   	struct fname tmp;
	struct dirent *dir;
    	struct stat buf;
	if(arg[arg_len-1] != '/')
	{	
		if(arg_len+2 > PATH_MAX)	// 2 represents two characters - '/' and '\0'
		{
			printf("\nCan't concatenate '/' to %s, as new length exceeds max limit-%d",arg,PATH_MAX);
			exit(EXIT_FAILURE);			
		}
		strcat(arg,"/");
		arg_len += 1;
	}
	if(head)
	{
		//if head points to some node
		tmp_nxt = head->nxt;	
	}
    	dr = opendir(arg);
    	if(dr)
    	{
		puts(arg);
		while((dir = readdir(dr)) != NULL)
        	{
			if((arg_len+strlen(dir->d_name)) >= PATH_MAX)
			{
				printf("\nCan't concatenate %s to %s, as new length exceeds max limit-%d",dir->d_name,arg,PATH_MAX);
				exit(EXIT_FAILURE);
			}
            		strcat(arg,dir->d_name);
           		if(++count >= maxfiles)
            		{
               			//reallocate memory for fptr if entries in dir > MAXFILES
                		maxfiles += MAXFILES;
                		fptr = (struct fname *)realloc(fptr,maxfiles*sizeof(struct fname));
				if(!fptr)
				{
					printf("\n error allocating memory to f_ptr");
					exit(EXIT_FAILURE);
				}
			}
			strcpy(fptr[count].name,arg);
			arg[arg_len] = '\0';
        	}
		if(closedir(dr) < 0)
		{
			printf("Unable to close directory stream for - %s",arg);
			exit(EXIT_FAILURE);		
		}
		qsort(fptr,count+1,sizeof(struct fname),comparator);
		display(count);
		memset(fptr,0,maxfiles*(sizeof(struct fname)));
		if(maxfiles > MAXFILES)
		{	
    			fptr = (struct fname *)realloc(fptr,MAXFILES*(sizeof(struct fname)));
    			if(!fptr)
			{
				printf("\nerror reallocating fptr");
				exit(EXIT_FAILURE);
			}
			maxfiles = MAXFILES;
   		}		
    }
    else
    {
    	printf("\n error opening directory, %s",arg);
	printf("\n error:%d\n err msg:%s\n",errno,strerror(errno));
    }  
}
