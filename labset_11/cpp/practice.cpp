 #include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
void nonterminal (char );
int numofproduct,k,temp;
char productionset[10][10],str[20];
int result;
int main(void)
{
	int i,ch;
	printf("\n number of productions:");
	scanf("%d",&numofproduct);
	printf("\n enter the productions , enter # for epsilion");
	for(i=0;i<numofproduct;i++)
	{
		
			printf("\n enter the productions number %d : ",i+1);
		//	for(j=i;j<numofproduct;j++)
		//{
			scanf("%s",productionset[i]);
		//}
	}
	do
	{
		k=0;
		printf("\n enter the strings");
		//for(i=0;i<numofproduct;i++)
			scanf("%s",str);
		nonterminal(productionset[0][0]);
		if(k==strlen(str))
			printf("\n input string is valid");
		else
			printf("\n invalid string");
		printf("\n do u want to continue or not 1/2");
		scanf("%d",&ch);	
	}
	while(ch==1);
	return 0;
}

	
void nonterminal(char p)
{
	int i,j,found=0;
	for(i=0;i<numofproduct;i++)
	{
		temp =k;
		if(productionset[i][0]==p)
		{
			for(j=3;productionset[i][j]!='\0';j++)
			if(isupper(productionset[i][j]))
			{
				found =1;
				nonterminal(productionset[i][j]);
			}
			else if(productionset[i][j]==str[k])
			{
				k++;
				found =1;
			}
			else if(productionset[i][j]=='#')
			{
				found =1;
				return;
			}
		
			else
			{
				k=temp;
				break;
			}
		}
	}
	if((i>=numofproduct) && (found ==0) &&(k!=strlen(str)))
	{
		printf("\n invalid input:");
		exit(0);
	}
}
