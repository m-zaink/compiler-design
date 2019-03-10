//Author : karanpratap
//Program : First
//WARNING : This program is in the making. Please don't refer it just yet.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

bool flag=false;
bool last=false;

bool first(char productions[100][100],char ch,int n){
	
	return true;
}

int main(){
	int n,i;

	//input the productions
	printf("\nEnter the number of productions:");
	scanf("%d",&n);
	char productions[100][100];
	printf("\nEnter the productions (A->productions) (use # for epsilon):");
	for(i=0;i<n;i++){
		printf("\nEnter the production no %d:",i+1);
		scanf("%s",productions[i]);
	
	}

	getchar();
	
	//logic for first
	
	char ch='y';
	do{
		printf("\nEnter the symbol for which first is to be calculated:");
		scanf("%c",&ch);
		printf("First of %c: {",ch);
		fflush(stdin);
		first(productions,ch,n);
		fflush(stdin);
		printf(" }");
		flag=false;
		printf("\nEnter more?(y/n)");
		getchar();
		scanf("%c",&ch);
		getchar();
	}while(ch=='Y' || ch=='y');
	return 0;

}
