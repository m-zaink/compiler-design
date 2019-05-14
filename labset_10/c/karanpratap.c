//Author : karanpratap
//Program : Construction of predictive parsing table
//Bounty up : Anyone to find a logical fault along with detailed fix gets a free coke.

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

/*GLOBAL DECLARATIONS AND MAPPING:
- productions : A 2-D character array to hold the productions for the grammar
- nonTerminals : A character array to hold the non terminal symbols of the grammar
- terminals : A character array to hold the terminal symbols of the grammar
- first : A 2-D character array to hold symbols in the first of non-terminals, first[i] is a string holding firsts of the nonTerminal[i]
-follow : A 2-D character array to hold the symbols in the follow of non-terminals, follow[i] is a string holding follows of the nonTerminal[i]
- n : An integer to store the number of productions in the grammar
- terminalCount : An integer to store the number of terminals in the grammar
- nonTerminalCount : An integer to store the number of non-terminals in the grammar
- table : A 2-D array that stores the production numbers in their proper locations in the predictive parsing table. Here, table[i][j] refers to the entry M[nonTerminals[i],terminals[j]] in the predictive parsing table.
*/
char productions[100][100],nonTerminals[100],terminals[100],first[100][100],follow[100][100];
int n,terminalCount=0,nonTerminalCount=0,table[100][100];

/*FUNCTION : contains
This is a function which takes 2 input parameters - a character array and a target character, and returns the index at which the character is found in the array, -1 if the character is not found.
*/
int contains(char arr[],char target){
	int i;
	for(i=0;arr[i]!=target && arr[i]!='\0';i++);
	if(i<strlen(arr))
		return i;
	return -1;
}

/*FUNCTION : init
A simple function to initialize all the entries of the parsing table to -1. This is used later while displaying the table as is explained for the displayTable function.
*/
void init(){
	int i,j;
	for(i=0;i<100;i++)
		for(j=0;j<100;j++)
			table[i][j]=-1;
}

/*FUNCTION : locateTerminalsAndNonTerminals
A function to locate all the terminals and non-terminal symbols of the grammar from the productions input by the user.
OPERATION:
	- The function traverses each and every production of the grammar
	- Each character is examined:
		-- If the character is upper case and not in non-terminals array, it is added to the non-terminals array. nonTerminalCount variable is incremented
		-- If the character is NOT upper case and not in terminals array, it is added to the terminals array. terminalCount variable is incremented.
		-- However, these are not the only two cases. If the character is epsilon(#), or the position within the production is 1 or 2, no action has to be taken for these cases and we must move on the next character within the production.
NOTE : Positions 1 and 2 are skipped because the user input is expected of the form : A->productionBody, so the index 1 and 2 make up the '->'. These symbols must not be included in the terminals.
*/
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

/*FUNCTION : predictiveParsingTable
This is the function responsible for generating the predictive parsing table, or more accurately, mapping the productions by the number to their proper position in the table.

LOCAL VARIABLES:
	- i,j,k : loop counter variables
	- row : a temporary variable to store the index of the non terminal at the production head of the production under consideration, thus storing the row number of the predictive parsing table for this non-terminal(Refer to the mapping schematic shown at the end of the program)
	- position : A temporary variable for storing the index value of the terminal or non-terminal, whichever is encountered as the first symbol of the current production's body, in the terminals and nonTerminals array respectively
	- tempFirst : A temporary variable to store the index value of the terminal when traversing terminal symbols in the first of the non-terminal at the start of the production body
	- tempFollow : A temporary variable to store the index value of the terminal when traversing terminal symbols in the follow of the non-terminal at the current production head

OPERATION:
	- For each production in the grammar input by the user, contains function is used to store the index of the production head into row and then the first symbol in the body of the production is examined:
		-- If the body's first symbol is epsilon(#), we start traversing the follows of the nonTerminals[row], i.e the non-terminal at the head of the production, for each terminal in the follow:
			--- If the follow is not equal to '$', then find the index of the follow in terminals using contains function into tempFollow and then input the production number 'i' in the entry table[row][tempFollow]. This effectively maps the non-terminal to the terminal as in M[X,a].
			--- If the follow is equal to '$', then add the production number to the last column of the table, i.e beyond all terminals at table[i][terminalCount]
		-- If the body's first symbol is a terminal, find its position in the terminals array using contains function and map the production number to table[row][position]
		-- If the body's first symbol is a non-terminal, find its position in the nonTerminals array using contains function and then, for every symbol in the first[position]:
			--- Input the production number at the appropriate position in the table by finding the position of the first in the terminals array into tempFirst and then input the entry(Production number) at table[row][tempFirst].
			--- If the first is epsilon(#), repeat the steps as done for the case when the body's first symbol was #.
	-These steps are repeated for each and every production, finally generating the table with production numbers mapped to their proper locations. Empty cells are filled with -1.
*/
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

/*FUNCTION : displayTable
This function is used to display the predictive parsing table in proper format using the 2-D integer array table as generated by the function predictiveParsingTable
OPERATION:
	- The terminals are first displayed on the top and at the end $.
	- For each non-terminal in the nonTerminals array:
		-- Print the non-terminal first.
		-- Then, using the table 2-D array, print for this non-terminal, the production, i.e productions[table[i][j]]
		-- Print a new line in the end of each non-terminal
*/
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

/*FUNCTION : main
Performs all driver tasks and handles inputs and function calls.
OPERATION:
	- Calls init()
	- Takes in the number of productions 'n' and then the productions of the grammar as strings into 'productions'
	- Calls locateTerminalsAndNonTerminals and displays the terminals and non-terminals.
	- Takes in first and follow symbols for the non-terminals from the user into 'first' and 'follow' character arrays. The input is expected as strings without spaces.
	- predictiveParsingTable function is called to fill in the 2-D integer array 'table' accordingly
	- displayTable function is called to display the predictive parsing table as defined earlier.
*/
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

SCHEMATIC MAPPING:
==================


        M                               terminals[0]                terminals[1]                terminals[2]    terminals[3]    ....    terminals[terminalCount-1]      $
    nonTerminals[0]                     productions[table[0][0]]    productions[table[0][1]]    ...             ...                     ...                             ...	
    nonTerminals[1]                     ...                         ...                         ...             ...                     ...                             ...
    nonTerminals[2]                     ...                         ...                         ...             ...                     ...                             ...
        .
        .
        .
    nonTerminals[nonTerminalCount-1]    ...                         ...                         ...             ...                     ...                             ...



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
