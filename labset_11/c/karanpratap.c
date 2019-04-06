//AUTHOR : karanpratap
//Program : Using recursive descent parsing to check the validity of the input string
//Note: This is the ALPHA release. Test the code as you refer. Logical bug hunters are 
//		always respected in my world.
//PS: This program is designed taking the assumption that there's only one start production.
//BOUNTY UP: The one to report a logical bug along with a fix gets a free coke.

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>

/*
Global Variable Declarations:
	*productions: A 2-D character array, i.e an array of strings to store the productions of
				  the grammar.
	*terminals: A character array to store the terminals in the grammar as the productions 
				are read.
	*string: A string to store the input string to be validated against the productions.
	*pointer: An integer variable to point to the next symbol to be read from the 
			  input string.
	*n: The number of productions; read from the user.
	*terminalcount: An integer to dynamically store the number of terminals as they are read.
*/
char productions[100][100],terminals[100];
char string[100];
int pointer=0;
int n,terminalcount=0;

/*
A function which simply checks whether a character is already present in a character array.
Returns true if it is present; false otherwise.
*/
bool in(char ch,char* arr){
	int i;
	for(i=0;i<n;i++){
		if(ch==arr[i])
			return true;
	}
	return true;
}

/*
The function responsible for checking whether an encountered non-terminal in the production
is correct for the given input string or not. Returns true if it is; false otherwise.
Operation:*Traverses all productions to find the one which corresponds to the given non
		   terminal for which the this function was called.
		  *For all such productions, traverse the body of the production; if the symbol read
		   is a terminal, check if the current symbol is equal to the next symbol in the
		   input string.
		  	-If it is, increments the pointer position by one and moves on to the next symbol
			-Else, break the loop and find the next production corresponding to the given 
			 input non-terminal. Also, reduce the pointer position by the amount it was 
			 increased in this particular function call, effectively backtracking.
		  *If the encountered symbol is a non-terminal, then call this procedure recursively.
		   	-If it returns true,continue traversal, else backtrack and check for the next
			 production corresponding to the previous non-terminal read.
			-In the end of traversal of the body of the production, if the entire body was
			 traversed successfully without breaking, then return true, i.e this non-terminal
			 is valid and we can move on to the next symbol. Else, return false.
NOTE: The counter variable maintains a count of the number of times the pointer was 
	  incremented in this particular recursive call. This aids in backtracking in case this
	  production is invalid and we need to move on to the next production.
UPDATE:    In case epsilon is encountered(#), we need to continue the traversal within the 
		   body of the production without incrementing the pointer.

*/
bool procedure(char ch){
	int i,counter=0;
	for(i=0;i<n;i++){
		if(productions[i][0]==ch){
			int j,len=strlen(productions[i]);
			for(j=3;j<strlen(productions[i]);j++){
				if(islower(productions[i][j])){
					if(productions[i][j]==string[pointer]){
						pointer++;
						counter++;
						continue;
					}
					else{
						pointer-=counter;
						break;
					}
				}
				else if(productions[i][j]=='#')
					continue;
				else{
					if(!procedure(productions[i][j])){
						pointer-=counter;
						break;
					}
				}
			}
			if(j==len)
				return true;
		}
	}
	return false;
}

/*
This function is the starting point for the validation process. The starting symbol is passed
to this function.
Operation:*Traverses all productions to find the one starting with the given start symbol.
		  *Traverses the body of that production; if the symbol read is a terminal, checks
		   if the current symbol is equal to the next symbol in the input string.
		   	-If it is, increments the pointer position by one and moves on to the next symbol
			 in the production body.
			-Else, directly returns false.
		  *If the encountered symbol is a non-terminal, a procedure is called for that symbol
		   which returns true if the given non-terminal is valid for the given input string,
		   otherwise false.
		  	-If the procedure returns true, we continue with the traversal, else we return 
			 false, i.e the input string will not be accepted.
		  *If the loop is successfully traversed, this implies that no failure condition was 
		   encountered in between and that the input string was validated using the input 
		   grammar. Thus returns true if the pointer is at the end of the input string else
		   false.
UPDATE:    In case epsilon is encountered(#), we need to continue the traversal within the 
		   body of the production without incrementing the pointer.
*/
bool startProcedure(char ch){
	int i;
	for(i=0;i<n;i++){
		if(productions[i][0]==ch){
			int j;
			for(j=3;j<strlen(productions[i]);j++){
				if(islower(productions[i][j])){
					if(productions[i][j]==string[pointer]){
						pointer++;
						continue;
					}
					else{
						return false;
					}
				}
				else if(productions[i][j]=='#'){
					continue;
				}
				else{
					if(!procedure(productions[i][j]))
						return false;
				}
			}
		}
	}
	if(pointer==strlen(string))
		return true;
	else
		return false;
}

/*
Main function:
Takes in the number of productions, the productions into a string array, the start symbol and
the input string to be validated using recursive descent parsing.
It then calls the startProcedure function of the start symbol specified by the user. If this
function returns true, the string is accepted, otherwise rejected and the suitable message is
printed.
UPDATE: The user can now enter strings to be validated in a loop for a given grammar and can
		stop willingly by providing 'n' or 'N' as the input for the choice provided.
*/
int main(){
	int i;
	char start,ch;
	printf("\nEnter the number of productions:");
	scanf("%d",&n);
	printf("\nEnter all the productions in the form - A->productionBody\n");
	for(i=0;i<n;i++){
		printf("\nEnter the production number %d:",i+1);
		scanf("%s",productions[i]);
		int j;
		for(j=0;j<strlen(productions[i]);j++){
			if(islower(productions[i][j]) && !in(productions[i][j],terminals))
				terminals[terminalcount++]=productions[i][j];
		}
	}
	getchar();
	printf("\nEnter the start symbol:");
	scanf("%c",&start);
	do{
		printf("\nEnter the string to be validated:");
		scanf("%s",string);
		getchar();
		if(startProcedure(start))
			printf("ACCEPTED!");
		else
			printf("REJECTED");
		printf("\nEnter more strings to be validated?(N or n to stop):");
		scanf("%c",&ch);
		pointer=0;
	}while(ch!='N' && ch!='n');
	return 0;
}

/*
SAMPLE OUTPUT
=============

OUTPUT 1:
---------

Enter the number of productions:3

Enter all the productions in the form - A->productionBody

Enter the production number 1:S->rXd

Enter the production number 2:X->aYc

Enter the production number 3:Y->w

Enter the start symbol:S

Enter the string to be validated:rawcdi
REJECTED

OUTPUT 2:
---------

Enter the number of productions:3

Enter all the productions in the form - A->productionBody

Enter the production number 1:S->rXd

Enter the production number 2:X->aYc

Enter the production number 3:Y->w

Enter the start symbol:S

Enter the string to be validated:rawcd
ACCEPTED!

*/
