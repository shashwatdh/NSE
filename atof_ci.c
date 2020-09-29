#include<stdio.h>
#include<math.h>
int atofci(char *str,double *inf,int size)
{
	//first check if array has enough space
	// -1, if special char is encountered
	// -2, if not enough space
	// -3, if 0 or -ve no is entered / if limit exceeds
	// -4, for out of range 
	// -5, if no. of argumnets !=4
	// this function can't handle very large floating no and hence wrong o/p will be computed
	int i,start=0,flag=0,ip=0,len;
	//char str[10000];
	int digits,dec_pos,ips=0,loop_br=0,dec_present=0;
	double no,princ,rate;
	float yrs,id;
	double limit_d=pow(2,8*sizeof(double))-1;
	float limit_f=pow(2,8*sizeof(float))-1;
	len=strlen(str);
	//printf("size of array:%d,addr of array:%u",sizeof(*inf),inf);
	if(size>=4)
	{
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
				/*if(ips==1)
				{
					printf("\n id can only be integer!");
					break;
				}*/
				if(!flag)
					digits=0;
				dec_pos=digits;
				dec_present=1;
			}
			else if(str[i]==' '||str[i]=='\t')
			{
				if(flag)
				{
					switch(ips)
					{
						case 1:	id=(!dec_pos && !dec_present)?no:no/pow(10,(digits-dec_pos));
								printf("\n processed id!-%lf",id);
								break;
						case 2:	princ=(!dec_pos && !dec_present)?no:no/pow(10,(digits-dec_pos));
								printf("\n processed princ!-%lf",princ);
								if(princ<=0 || princ>limit_d)
									loop_br=1;
								break;
						case 3:	rate=(!dec_pos && !dec_present)?no:no/pow(10,(digits-dec_pos));
								printf("\n processed rate!-%lf",rate);
								if(rate<=0 || rate>limit_d)
									loop_br=1;
								break;
						//case 4:yrs=no/pow(10,(digits-dec_pos));printf("\n processed yrs!");break;
						default:printf("\n random-%d",ips);break;
					}
				}
				flag=0;
				digits=0;
				dec_present=0;
				if(loop_br)
				{
					printf("\n princ,rate and time should be >0 & <%lf",limit_d);
					return -3;
					//break;
				}
			}
			else
			{
				printf("\n no other characters except 0-9 & . are allowed!");
				return -1;
				//break;
			}
		}
		if(ips==4)
		{
			yrs=(!dec_pos && !dec_present)?no:no/pow(10,(digits-dec_pos));
			printf("\n processed yrs!");
			if(yrs<=0 || (float)yrs>limit_f)
			{
				printf("\n princ,rate and time should be >0 & <%lf",limit_d);
				
			}
			printf("\n id:%f",id);
			printf("\n princ:%lf",princ);
			printf("\n rate:%lf",rate);
			printf("\n yrs:%f",yrs);
			inf[0]=id;
			inf[1]=princ;
			inf[2]=rate;
			inf[3]=yrs;
		}
		else
		{
			printf("\n no. of args should be 4");
			return -5;
		}
	}
	else
		return -2;
	return 1;
}