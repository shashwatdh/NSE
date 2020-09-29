#include<stdio.h>
#include<math.h>
double ci(double princ,double rate,float yrs)
{
	return (princ*pow((1+(rate/100)),(yrs)));
}