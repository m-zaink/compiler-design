//Author : nateshmbhat
//Program : Closure of an item

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
int addedProductions[100] = {0} ; 

void closure(char target){
    if(!isupper(target)) return ; 
    for(int i =0 ;i < n ;i++){
        if(target == productions[i][0] && addedProductions[i]==0)
        {
            printf("%c%c%c.%s\n" , target , '-','>' , productions[i]+3) ; 
            addedProductions[i]+=1 ;
            closure(productions[i][3]) ; 
        }
    }
}


int main(){
	int i;
	char target;
	printf("\nEnter the number of productions:");
	scanf("%d",&n);
	printf("\nEnter the productions of the grammar:");
	for(i=0;i<n;i++) scanf("%s",productions[i]);
	getchar();
	printf("\nEnter the item for which closure is to be calculated:");
    scanf("%s",item); getchar();
    for(i=0;item[i]!='\0';i++){
        if(item[i]=='.'){
            if(i==strlen(item)-1)
                target='#';
            else
                target=item[i+1];
            break;
        }
    }
	printf("\nClosure Set of (%s):\n %s\n",item, item);
	closure(target);
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


========================================

Enter the number of productions:5

Enter the productions of the grammar:
S->ABC
A->BC
B->C
C->SD
D->a

Enter the item for which closure is to be calculated:A->B.C

Closure Set of (A->B.C):
A->B.C
C->.SD
S->.ABC
A->.BC
B->.C

*/
