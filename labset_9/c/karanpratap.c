//Author : karanpratap
//Program : First of a given symbol in the given grammar
//UPDATE : INSTEAD OF DIRECTLY PRINTING, THE PROGRAM NOW STORES THE SYMBOLS IN FIRST OF A GIVEN 
//		   SYMBOL TO A CHARACTER ARRAY.
//NOTE : DO REFER AND TEST FOR ERRORS. FIRST PERSON TO POINT OUT A LOGICAL ERROR ALONG WITH FIX
//		 GETS A FREE COKE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

/*
k - a variable to keep count of the number of terminals
terminals - A character array to store all the terminals encountered in the given productions
printChar - A character variable to store the current terminal to be printed in case it is
encountered during calculation of first.
firsts - A character array to store the symbols in first of the current symbol under consideration
firstCounter - Number of first symbols found for the current symbol
flag - a boolean which is set when an epsilon is encountered. Used in deciding whether to add 
epsilon to the firsts or not.
*/
int k=0;
char terminals[100];
char printChar;
char firsts[100];
int firstCounter=0;
bool flag=false;

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
Operation : *If the input symbol is a terminal of the given grammar, its first will be the symbol itself. This symbol is
			added to the firsts if it is not already there.
			*If the character is epsilon(here #), then we simply return true and make flag as true. We cant add epsilon 
			just yet as there may be more symbols following this symbol.
			*Otherwise, the symbol is a non-terminal It will check for this symbol's productions. If found, it
			 checks the body part of its production and recursively calls itself on the symbols of that production,
			 following these rules:
			 	-If epsilon is encountered, it goes on to the next symbol in the body of the production.
				-If a terminal is encountered, it adds it to first and comes out of THIS production and goes on
				 to find other productions starting with the non-terminal on which the function was called.
				-If a non-terminal is encountered, it calls itself recursively for that symbol and these steps are
				 repeated.
			*This finally results in all the symbols in the first of the requested symbol to be printed.
			UPDATE: counter here is used to mark the depth of recursion; if counter==0, then this is the first function
			call and recursion has not yet begun.
			UPDATE: If we are currently in the first call and epsilon is encountered then we definitely need to add epsilon
			to the first of the given symbol, that is what condition (*) does.
*/
bool first(char productions[100][100],char ch,int n,int counter){
	int i,j;
	if(islower(ch) && in(ch,terminals,k)){
		if(!in(ch,firsts,firstCounter))
			firsts[firstCounter++]=ch;
		return false;
	}
	else if(ch=='#'){
		flag=true;
		return true;
	}

	for(i=0;i<n;i++){
		if(productions[i][0]==ch){
			for(j=3;productions[i][j]!='\0';j++){
				if(first(productions,productions[i][j],n,counter+1) && flag && counter==0 && j==strlen(productions[i])-1){ // *
					if(!in('#',firsts,firstCounter))
						firsts[firstCounter++]='#';
					flag=false;
					continue;
				}
				else if(first(productions,productions[i][j],n,counter+1) || flag){
					flag=false;
					continue;
				}
				else
					break;
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
		fflush(stdin);
		first(productions,ch,n,0);
		int l;
		printf("First of %c : {",ch);
		for(l=0;l<firstCounter;l++)
			printf(" %c ",firsts[l]);
		printf("}\n");
		firstCounter=0;
		fflush(stdin);
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
