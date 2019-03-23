//Author : karanpratap
//Program : First of a given symbol in the given grammar

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

/*
flag - a boolean for checking the encounter of epsilon
//k - a variable to keep count of the number of terminals
//terminals - A character array to store all the terminals encountered in the given productions
*/
bool flag=false;
int k=0;
char terminals[100];


//This function checks whether a given terminal is already present in the terminals array
bool in(char ch,char arr[100],int n){
	int i;
	for(i=0;i<n;i++)
		if(arr[i]==ch)
			return true;
	return false;
}

/*
This is the recursive function where the first is calculated for a given symbol. Returns true if epsilon is encountered
Operation : *If the input symbol is a terminal of the given grammar, its first will be the symbol itself.
			*If the character is epsilon(here #), then we simply return true. We cant print epsilon just yet 
			 as there may be more symbols following this symbol.
			*Otherwise, the symbol is a non-terminal It will check for this symbol's productions. If found, it
			 checks the body part of its production and recursively calls itself on the symbols of that production,
			 following these rules:
			 	-If epsilon is encountered, it goes on to the next symbol in the body of the production.
				-If a terminal is encountered, it adds it to first and comes out of THIS production and goes on
				 to find other productions starting with the non-terminal on which the function was called.
				-If a non-terminal is encountered, it calls itself recursively for that symbol and these steps are
				 repeated.
			*This finally results in all the symbols in the first of the requested symbol to be printed.
*/
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

/*
Main function : 
	Takes in the number of productions along with the productions in the form of NONTerminal->Production
	Following this is a loop which lets the user to input any symbol of the grammar whose first is to be
	found. The loop stops when the user inputs any character other than y or Y.
*/
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

/*
SAMPLE OUTPUT
=============

Enter the number of productions:4

Enter the productions (A->productions) (use # for epsilon):
Enter the production no 1:A->BCD

Enter the production no 2:B->#

Enter the production no 3:C->cD

Enter the production no 4:D->dC

Enter the symbol for which first is to be calculated:A
First of A: { c  }
Enter more?(y/n)y

Enter the symbol for which first is to be calculated:B
First of B: { #  }
Enter more?(y/n)y

Enter the symbol for which first is to be calculated:C
First of C: { c  }
Enter more?(y/n)y

Enter the symbol for which first is to be calculated:D
First of D: { d  }
Enter more?(y/n)n

*/
