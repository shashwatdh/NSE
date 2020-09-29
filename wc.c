#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
void main(int argc,char *argv[])
{
	long long unsigned int nc,nw,nl;
	char ch;
	int flag=0;
	nc=nw=nl=0;
	FILE *fp;
	//printf("%lf\n",pow(2,8*sizeof(nc))-1);
	if(argc==2)
	{
		if((fp=fopen(argv[1],"r"))!=NULL)
		{
			while((ch=fgetc(fp))!=EOF)
			{
				++nc;
				if(ch!=' '&& ch!='\t' && ch!='\n')
				{
					if(!flag)
					{
				   		++nw;
				   		flag=1;	
					} 
				}
				else
				{
					if(flag)
				  		flag=0;
					if(ch=='\n')
				   		++nl;  
				}
			}
			printf("%llu %llu %llu %s",nl,nw,nc,argv[1]);
			fclose(fp);	
		}
		else
			printf("\n error opening file");
	}
	else
		printf("\n enter filename!");
}
