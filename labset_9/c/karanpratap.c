//Author : karanpratap
//Program : First

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

bool flag=false;
int k=0;
char terminals[100];

bool in(char ch,char arr[100],int n){
	int i;
	for(i=0;i<n;i++)
		if(arr[i]==ch)
			return true;
	return false;
}

bool first(char productions[100][100],char ch,int n){
	int i,j;
	if(islower(ch) && in(ch,terminals,k)){
		printf(" %c ",ch);
		return false;
	}
	else if(ch=='#'){
		return true;
	}

	for(i=0;i<n;i++){
		if(productions[i][0]==ch){
			for(j=3;productions[i][j]!='\0';j++){
				if(first(productions,productions[i][j],n))
					continue;	
				else
					return false;
			}
		}
	}
	return true;
}

int main(){
	int n,i=0;
	//input the productions
	printf("\nEnter the number of productions:");
	scanf("%d",&n);
	char productions[100][100];
	printf("\nEnter the productions (A->productions) (use # for epsilon):");
	for(i=0;i<n;i++){
		printf("\nEnter the production no %d:",i+1);
		scanf("%s",productions[i]);
		int j=0;
		for(j=0;j<strlen(productions[i]);j++){
			if(islower(productions[i][j]) && !(in(productions[i][j],terminals,k)))
				terminals[k++]=productions[i][j];
		}
		fflush(stdin);
	}
	getchar();
	//logic for first
	fflush(stdin);	
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
