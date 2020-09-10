#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
	int tab[10][10],i,j,num,d,sum=0,sum1=0,k,counter=0;
	printf("Podaj wartosc:");
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			
			d=scanf("%d",&num);
			tab[i][j]=num;
			if(d!=1)
			{
				printf("incorrect input");
				return 1;
			}
		
		}
		
	}
	int max=tab[0][0];
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			
			if((tab[i][j]%2)==0&&tab[i][j]>=max)
			{
				max=tab[i][j];
				counter++;
			}
			
		}
		
	}
	if(counter==0)
	{
		printf("Nothing to show");
	}
	else
	{
	
		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)
			{
			
				if(max==tab[i][j])
				{
					for(k=0;k<10;k++)
					{
					sum+=tab[i][k];
					sum1+=tab[k][j];
					}
					printf("%d %d %d\n",j,i,sum-sum1);
					sum=0;
					sum1=0;
				}
			}
		
		}
	}
	
	return 0;	
}
