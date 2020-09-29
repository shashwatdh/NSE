#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
#include<limits.h>
void id_inf(char *user)
{
	int ngroups=9,j,i,len,nc=0,found=0,complete=0,k=0;
	char buf[PATH_MAX];
	//int uid,gid;
	uid_t uid;
	gid_t gid;
	FILE *fp;
	gid_t *groups;
	struct passwd *uinf;
	struct group *gr;
	long ngroups_max;
    ngroups_max = sysconf(_SC_NGROUPS_MAX);
    groups=(gid_t*)calloc(ngroups_max,sizeof(gid_t));
	if(strcmp(user," ")==0)
	{
		
		uinf=getpwuid(getuid());
		user=uinf->pw_name;
		uid=uinf->pw_uid;
		gid=uinf->pw_gid;
	}
	else
	{
	    
		fp=fopen("/etc/passwd","r");
        if(fp==NULL)
        {
  		   printf("\n error opening file");
		   return;	
		}
		 
		while(!feof(fp))
		{
 			
			fgets(buf,PATH_MAX,fp);
			len=strlen(buf);
			for(i=0;i<len;i++)
			{
				if(buf[i]==':')
				{
					buf[i]='\0';
					switch(++nc)
					{
						case 1: if(strcmp(buf,user)==0)
								{ // printf("\nfound-%s",buf);
									found=1;
								}
								break;
						case 2: uid=i+1;
						        break;
						case 3: uid=atoi(buf+uid);
						        gid=i+1;
						        break;
						case 4: gid=atoi(buf+gid);
						        complete=1;found=0;
						        break;
						default: printf("\n wrong ncount");break;
					}
					if(!found)
					{     
						nc=0;
						break;
					}
				}
				
			}
			if(complete)
			  break;
		}
		if(!complete)
		{
			printf("\n invalid user");
			return;
		}
	}
	gr=getgrgid(gid);
	printf("uid=%d(%s) gid=%d(%s)  groups=",uid,user,gid,gr->gr_name);
	if(getgrouplist(user,gid,groups,&ngroups) == -1) 
	{
        getgrouplist(user,gid,groups,&ngroups);
    }
           
    for (j = 0; j < ngroups; j++) 
    {
        printf("%d", groups[j]);
        gr = getgrgid(groups[j]);
        if (gr != NULL)
            printf("(%s)", gr->gr_name);
        if (j!=ngroups-1)printf(",");
    }
	
}
void main(int argc,char *argv[])
{
	int i;
	
	//if(argc>1)
	//{

	  //if(strcmp(argv[1],"id")==0)
	  //{
		
		if(argc==2)
		{
		  id_inf(argv[1]);
		}
		else
		{
		  //uinf=getpwuid(getuid());uinf->pw_name
		  id_inf(" ");
		}
	  
	  /*}
	  else
	    printf("\n unknown command '%s'",argv[i]);*/
	//}
	//else
	 //printf("\n enter id command");
}

