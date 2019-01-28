// Author  : mzaink
// Program : String matching.

#include<stdio.h>
#include<stdlib.h>
int main()
{
	char str[10];
	int i,n,state=0;
	
	printf("\nEnter the string :");
	gets(str);
	
	
	for(i=0;str[i]!='\0';i++)
	{
		switch(state)
		{
			case 0:if(str[i]=='a') state=1;
				else if (str[i]=='b') state=4;
				else state =6;
			break;
			case 1:if(str[i]=='a') state=5;
				else if (str[i]=='b') state=2;
				else state =6;
			break;
			case 2:if(str[i]=='b') state=3;
				else state =6;
			break;
			case 3:if(str[i]=='b') state=4;
				else state =6;
			break;
			case 4:if (str[i]=='b') state=4;
				else state =6;
			break;
			case 5:if(str[i]=='a') state=5;
				else if (str[i]=='b') state=4;
				else state =6;
			break;
			case 6:
				printf("\nINVALID STRING !!\n");
				exit(0);
		}
	}
	
	if(state==0||state==1||state==5)
		printf("\nThe string %s is recognized under 'a*' \n",str);
	else if(state==2||state==4)
		printf("\nThe string %s is recognized under 'a*b+' \n",str);
	else if(state==3)
		printf("\nThe string %s is recognized under 'abb' \n",str);
	else
		printf("\nThe string %s is invalid\n",str);
}


// Output [1] 
/*
	Enter the string :aaaaaab

	The string aaaaaab is recognized under 'a*b+' 

*/

// Output [2]
/*
	Enter the string :aaaaaab

	The string aaaaaab is recognized under 'a*b+' 
*/

// Output [3]
/*
	Enter the string :abb

	The string abb is recognized under 'abb' 
*/