//Author : karanpratap
//Program : Check the input string to check for a*, a*b+, abb

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Main Function:
	'string' variable stores the input string
	currentSymbol is used to store the current 
	character from the string under consideration.
	'state' variable stores the current state of the 
	transition process

	Returns: The type ( a*, a*b+ or abb ) of the input string
*/
int main(){
	char string[100],currentSymbol;
	int i,state=0;
	printf("\nEnter the Input String:");
	gets(string);
	for(i=0;i<strlen(string);i++){
		currentSymbol=string[i];
		switch(state){
			case 0:
				if(currentSymbol=='a')
					state=1;
				else if(currentSymbol=='b')
					state=3;
				else
					state=-1;
				break;
			case 1:
				if(currentSymbol=='a')
					state=2;
				else if(currentSymbol=='b')
					state=4;
				else
					state=-1;
				break;
			case 2:
				if(currentSymbol=='a')
					state=2;
				else if(currentSymbol=='b')
					state=3;
				else
					state=-1;
				break;
			case 3:
				if(currentSymbol=='a')
					state=-1;
				else if(currentSymbol=='b')
					state=3;
				else
					state=-1;
				break;
			case 4:
				if(currentSymbol=='a')
					state=-1;
				else if(currentSymbol=='b')
					state=5;
				else
					state=-1;
				break;
			case 5:
				if(currentSymbol=='a')
					state=-1;
				else if(currentSymbol=='b')
					state=3;
				else
					state=-1;
				break;
		}
	}

	switch(state){
		case -1:
			printf("\nInvalid String Input!");
			break;
		case 0:
		case 1:
		case 2:
			printf("\nValid String Input : [ a* ]");
			break;
		case 3:
		case 4:
			printf("\nValid String Input : [ a*b+ ]");
			break;
		case 5:
			printf("\nValid String Input : [ abb ]");
			break;
	}

	printf("\n");
	return 0;
}

/*
SAMPLE OUTPUT
=============

OUTPUT 1
--------

	Enter the Input String:aaaabbb
	
	Valid String Input : [ a*b+ ]

OUTPUT 2
--------

	Enter the Input String:abb

	Valid String Input : [ abb ]

OUTPUT 3
--------

	Enter the Input String:aaa

	Valid String Input : [ a* ]

OUTPUT 4
--------

	Enter the Input String:aaba

	Invalid String Input!
*/
