//Author : karanpratap
//Program : Construction of predictive parsing table
//Bounty up : Anyone to find a logical fault along with detailed fix gets a free coke.

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

char productions[100][100],nonTerminals[100],terminals[100],first[100][100],follow[100][100];
int n,terminalCount=0,nonTerminalCount=0,table[100][100];

int contains(char arr[],char target){
	int i;
	for(i=0;arr[i]!=target && arr[i]!='\0';i++);
	if(i<strlen(arr))
		return i;
	return -1;
}

void init(){
	int i,j;
	for(i=0;i<100;i++)
		for(j=0;j<100;j++)
			table[i][j]=-1;
}

void locateTerminalsAndNonTerminals(){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;productions[i][j]!='\0';j++){
			if(j==1 || j==2 || productions[i][j]=='#')
				continue;
			if(!isupper(productions[i][j]) && contains(terminals,productions[i][j])==-1)
				terminals[terminalCount++]=productions[i][j];
			else if(isupper(productions[i][j]) && contains(nonTerminals,productions[i][j])==-1)
				nonTerminals[nonTerminalCount++]=productions[i][j];
		}
	}
}

void predictiveParsingTable(){
	int i,j,row,position,tempFirst,tempFollow,k;
	for(i=0;i<n;i++){
		row=contains(nonTerminals,productions[i][0]);
		if(productions[i][3]=='#'){
			for(k=0;k<strlen(follow[row]);k++){
				if(follow[row][k]!='$'){
					tempFollow=contains(terminals,follow[position][k]);
					table[row][tempFollow]=i;
				}
				else
					table[row][strlen(terminals)]=i;
			}
		}
		else if(isupper(productions[i][3])){
			position=contains(nonTerminals,productions[i][3]);
			for(j=0;j<strlen(first[position]);j++){
				if(first[position][j]!='#'){
					tempFirst=contains(terminals,first[position][j]);
					table[row][tempFirst]=i;
				}
				else{
					//handle epsilon case by finding follows
					for(k=0;k<strlen(follow[row]);k++){
						if(follow[row][k]!='$'){
							tempFollow=contains(terminals,follow[position][k]);
							table[row][tempFollow]=i;
						}
						else
							table[row][strlen(terminals)]=i;
					}
				}
			}
		}
		else{
			position=contains(terminals,productions[i][3]);
			table[row][position]=i;
		}
	}
}

void displayTable(){
	int i,j;
	printf("\nPREDICTIVE PARSING TABLE:\n=================================\n");
	printf("\n%5c",'M');
	for(i=0;i<terminalCount;i++)
		printf("%8c",terminals[i]);
	printf("%8c\n",'$');
	for(i=0;i<nonTerminalCount;i++){
		printf("%5c",nonTerminals[i]);
		for(j=0;j<=terminalCount;j++)
			printf("%8s",productions[table[i][j]]);
		printf("\n");
	}
}

int main(){
	int i,j;
	init();
	printf("\nEnter the number of productions in the grammar:");
	scanf("%d",&n);
	printf("\nEnter the productions (A->production)");
	printf("\nWrite terminals with small letters and non-terminals with capital letters:\n");
	for(i=0;i<n;i++){
		scanf("%s",productions[i]);
		getchar();
	}
	locateTerminalsAndNonTerminals();
	printf("Terminals: ");
	for(i=0;i<terminalCount-1;i++)
		printf("%c, ",terminals[i]);
	printf("%c",terminals[terminalCount-1]);
	printf("\nNon-Terminals: ");
	for(i=0;i<nonTerminalCount-1;i++)
		printf("%c, ",nonTerminals[i]);
	printf("%c",nonTerminals[nonTerminalCount-1]);
	
	printf("\n");
	printf("Enter the first of the following Non-Terminals ('#' for epsilon):\n");
	for(i=0;i<nonTerminalCount;i++){
		printf("%c: ",nonTerminals[i]);
		scanf("%s",first[i]);
		getchar();
	}
	
	printf("Enter the follow of the Non-Terminals:\n");
	for(i=0;i<nonTerminalCount;i++){
		printf("%c: ",nonTerminals[i]);
		scanf("%s",follow[i]);
		getchar();
	}

	predictiveParsingTable();
	displayTable();

	printf("\n");
	return 0;
}

/*

This sample output shows the predictive parsing table for non-recursive standard 
expression grammar. Note that the program is not designed to eliminate left recursion.

SAMPLE OUTPUT:
==============

Enter the number of productions in the grammar:8

Enter the productions (A->production)
Write terminals with small letters and non-terminals with capital letters:
E->TG
G->+TG
G->#
T->FH
H->*FH
H->#
F->(E)
F->i
Terminals: +, *, (, ), i
Non-Terminals: E, T, G, F, H
Enter the first of the following Non-Terminals ('#' for epsilon):
E: i(
T: i(
G: +#
F: i(
H: *#
Enter the follow of the Non-Terminals:
E: $)
T: +$)
G: $)
F: *+$)
H: +$)

PREDICTIVE PARSING TABLE:
=================================

    M       +       *       (       )       i       $
    E                   E->TG           E->TG
    T                   T->FH           T->FH
    G  G->+TG                    G->#            G->#
    F                  F->(E)            F->i
    H    H->#  H->*FH            H->#            H->#

*/
