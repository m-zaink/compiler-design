//Author : karanpratap
//Program : Closure of an item
//Not thoroughly tested. No bounties up

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*Global Declerations:
-productions : holds all the productions as strings in the grammar
-closureNumber : number of items in the closure set of the given item
-n : number of productions in the grammar
*/
char productions[100][100],item[100];
int n,closureNumber=1;

/*Function : Closure
This is recursive function which takes in the symbol following the . and prints out the items in the closure Set.
Operation : 
	-The character following . is passed to this function through target variable.
	-If the target is a terminal, we don't need to calculate anything
	-If the target is a non-teminal, we select its productions from the grammar and use them to find items to be included in its closure.
	-We recursively repeat this operation for every production AND we apply a simple condition to verify that the body of the production's first symbol is not equal to the head of the production
		--If it is equal to the head, we need not to recursively call the function for that as it will lead to infinite recursive calls.
	-This procedure is repeated for each and every production until we have all the required items in the closure set.
UPDATE : The closureNumber variable is incremented each time we find a valid production.
*/
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

/*Function : Main
Local Variables : 
	- i : loop variable for traversing the item string to find the target
	- repeat : variable to control the do-while loop for accepting the item string
	- target : The symbol just following the . in item
Operation :
	-The user enters the number of productions in the grammar and then the productions as n strings
	-A do-while loop is implemented to validate the input of item. If the item string entered by the user does not contain '.', it is flagged invalid and the user is prompted to re-enter it
	-The function closure is then called with the 'target' symbol as the parameter which then further finds out the items in the closure of the input item using the operation mechanism as 
	 defined earlier.
	-The number of items in the closure set(closureNumber) is then output
*/
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
	printf("\nClosure Set of (%s):",item);
	printf("\n%s",item);
	closure(target);
	printf("\nNumber of elements in closure set=%d\n",closureNumber);
	printf("\n");
	return 0;
}

/*
SAMPLE OUTPUT :

Enter the number of productions:4 

Enter the productions of the grammar:A->BC
B->bC
C->dB
B->BcC

Enter the item for which closure is to be calculated:A->.BC

Closure Set of (A->.BC):
A->.BC
B->.bC
B->.BcC
Number of elements in closure set=3

*/
