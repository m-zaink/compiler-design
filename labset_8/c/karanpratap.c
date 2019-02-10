//Author : karanpratap
//Program : Checking for a valid C identifier

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
Main function:
	Takes in an input string in 'string' variable and checks whether
	it is valid or not
	
	NOTE:A valid C identifier starts with a alphabet/underscore and can then contain 
	any alphanumeric characters; but no special characters.
	
	Regex: [_a-zA-Z][_a-zA-Z0-9]*
*/
int main(){
	char string[100],currentSymbol;
	int i,state=0;
	printf("\nEnter the input string to be checked for identifier:");
	gets(string);
	for(i=0;i<strlen(string);i++){
		currentSymbol=string[i];
		switch(state){
			case 0:
				if(isalpha(currentSymbol) || currentSymbol=='_')
					state=1;
				else 
					state =-1;
				break;
			case 1:
				if(isalnum(currentSymbol) || currentSymbol=='_')
					state=1;
				else
					state=-1;
				break;
		}
		if(state==-1)
			break;
	}

	if(state==-1)
		printf("\nNOT a valid C identifier!");
	else
		printf("\nValid C identifier!");
	
	printf("\n");
	return 0;
}

/*
SAMPLE OUTPUT
=============

OUTPUT 1
--------

	Enter the input string to be checked for identifier:abb1

	Valid C identifier!

OUTPUT 2
--------

	Enter the input string to be checked for identifier:1ac

	NOT a valid C identifier!

OUTPUT 3
--------

	Enter the input string to be checked for identifier:_111

	Valid C identifier!

OUTPUT 4
--------

	Enter the input string to be checked for identifier:_kp#  

	NOT a valid C identifier!

*/
