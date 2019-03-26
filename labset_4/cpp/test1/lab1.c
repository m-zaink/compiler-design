#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
	int i,state=0;
	char str[20];
	printf("\n enter a string \n");
	gets(str);
	for(i=0;str[i]!='\0';i++)
	{
		switch(state)
		{
			case 0: if(str[i]=='a')
					state =1;
				else if(str[i]=='b')
					state=4;
				else 
					state=6;
				break;
			case 1: if(str[i]=='a')
					state =5;
				else if(str[i]=='b')
					state=2;
				else 
					state=6;
				break;
			case 2: if(str[i]=='a')
					state =1;
				else if(str[i]=='b')
					state=3;
				else 
					state=6;
				break;
			case 3: if(str[i]=='b')
					state=4;
				else 
					state=6;
				break;
			case 4: if(str[i]=='b')
					state=3;
				else 
					state=6;
				break;
			case 5: if(str[i]=='a')
					state =5;
				else if(str[i]=='b')
					state=4;
				else 
					state=6;
				break;
			case 6:printf("\n invalid input \n");
				exit(0);
		}
	}
	if(state == 0 || state == 1 || state == 5)
		printf("\n %s string is in a*",str);
	else if(state ==2 || state ==4)
		printf("\n %s string is in a*b+",str);
	else if(state ==3)
		printf("\n %s string is in abb",str);
	else 
		printf("\n not found \n");
	return 0;
}
