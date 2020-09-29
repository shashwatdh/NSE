#include<stdio.h>
#include<math.h>
#include<string.h>
double ci(double princ,double rate,float yrs)
{
	return (princ*pow((1+(rate/100)),yrs));
}
void main()
{
	char str[10000];
	int i,len,flag=0,digits,dec_pos,ips=0,loop_br=0,dec_present=0;
	double no,princ,rate;
	float yrs,id;
	while(!feof(stdin))
	{
		ips=0;flag=0,loop_br=0,dec_present=0;
		printf("\n Enter space seperated i/p:");
		gets(str);
		len=strlen(str);
		for(i=0;i<len;i++)
		{
			if(str[i]>='0' && str[i]<='9')
			{
				if(!flag)
				{
					flag=1;
					ips++;
					no=dec_pos=digits=0;
				}
				no=no*10+(str[i]-'0');
				++digits;
			}
			else if(str[i]=='.')
			{
				if(!flag)
					digits=0;
				dec_present=1;
				dec_pos=digits;
			}
			else if(str[i]==' '||str[i]=='\t')
			{
				if(flag)
				{
					switch(ips)
					{
						//case 1:id=no;printf("\n processed id!-%lf",id);break;
						case 1:	princ=(!dec_pos && !dec_present)?no:no/pow(10,(digits-dec_pos));
								printf("\n processed princ!-%lf",princ);
								if(princ<=0)
									loop_br=1;
								break;
						case 2:	rate=(!dec_pos && !dec_present)?no:no/pow(10,(digits-dec_pos));
								printf("\n processed rate!-%lf",rate);
								if(rate<=0)
									loop_br=1;
								break;
						//case 4:yrs=no/pow(10,(digits-dec_pos));printf("\n processed yrs!");break;
						//default:printf("\n random-%d",ips);break;
					}
				}
				flag=0;
				digits=0;
				dec_present=0;
				if(loop_br)
				{
					printf("\n princ,rate and time should be >0");
					break;
				}	
			}
			else
			{
				printf("\n no other characters except 0-9 & . are allowed!");
				break;
			}
		}
		if(ips==3)
		{
			yrs=(!dec_pos && !dec_present)?no:no/pow(10,(digits-dec_pos));printf("\n processed yrs!");
			if(yrs<=0)
			{
				printf("\n princ,rate and time should be >0");
				continue;
			}
			printf("\n princ:%lf",princ);
			printf("\n rate:%lf",rate);
			printf("\n yrs:%f",yrs);
			printf("\nci:%lf",ci(princ,rate,yrs));
		}
		else
		 printf("\n no. of args should be 3");
		//ips=0;flag=0;loop_br=0,dec_present=0;
	}
	//printf("Enter principal,rate,time");
	/*while(!feof(stdin))
	{
		printf("\n principal:");
		scanf("%lf",&princ);
		printf("\n Rate:");
		scanf("%lf",&rate);
		printf("\n Time:");
		scanf("%lf",&time);
		if(princ>0 && rate >0 && time>0)
			printf("\n%lf",ci(princ,rate,time));
		else
			printf("\n princ,rate and time must be >0");
	}*/
}