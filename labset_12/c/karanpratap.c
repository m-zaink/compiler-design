//Author : karanpratap
//Program : Closure of an item
//Not thoroughly tested. No bounties up

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char productions[100][100],item[100],closureSet[100][100];
int n,closureNumber=1;

void closure(char target){
	int i=0,j=0,k=0;

	if(islower(target) || target=='#')
		return;

	for(i=0;i<n;i++){
		if(productions[i][0]==target){

			//add item to the closure set
			closureNumber++;
			printf("\n");
			for(j=0;j<strlen(productions[i]);j++){
				printf("%c",productions[i][j]);
				if(j==2)
					printf(".");
			}
			//recursively check the production for further items derivable to be added to closure
			if(productions[i][0]!=productions[i][3] && isupper(productions[i][3]))
				closure(productions[i][3]);
		}
	}
}

int main(){
	int i;
	char repeat='y',target;
	printf("\nEnter the number of productions:");
	scanf("%d",&n);
	printf("\nEnter the productions of the grammar:");
	for(i=0;i<n;i++)
		scanf("%s",productions[i]);
	getchar();
	printf("\nEnter the item for which closure is to be calculated:");
	do{
		scanf("%s",item);
		for(i=0;item[i]!='\0';i++){
			if(item[i]=='.'){
				if(i==strlen(item)-1)
					target='#';
				else
					target=item[i+1];
				break;
			}
		}
		if(i<strlen(item)){
			repeat='n';
		}
		else
			printf("\nInvalid item. Please enter a valid item:");
		getchar();
	}while(repeat=='y');
	printf("\nNumber of elements in closure set=%d\n",closureNumber);
	printf("\nClosure Set of (%s):",item);
	printf("\n%s",item);
	closure(target);
	printf("\n");
	return 0;
}
