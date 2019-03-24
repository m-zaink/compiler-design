//Program : Find First(X) where X is a non terminal for a Grammar given a set of productions
//Author : nateshmbhat
#include<iostream>
#include<ctype.h>
#define MAX 256
using namespace std ;
int P ; //no of productions
char productions[MAX][MAX]; // Array of production strings

void addToResultSet(char target[] , char source[]){ //This function adds the elements(except epsilon) of a source set to the target set.
	for(int i =0 ; i < MAX ; i++){
		if(i=='#') continue ; 
		target[i]+=source[i] ; 
	}
}

void findFirst(char c , char result[] ){
	if(islower(c)||c=='#'){ result[c]++ ; return ; }
	char subResult[MAX] = { 0 }; 
	for(int i =0 ;i < P ; i++){// traverse through all the productions 
        if(productions[i][0]==c){//Non terminal on LHR matches with 'c'
            for(int j =3 ; productions[i][j]!='\0' ; j++){ //Traverse from 4th character till end of string
            	char symb = productions[i][j] ;
            	if(islower(symb)){ //First(X) found for current production . add it to result . Break from traversing the string and go for the next production
			result[symb]++ ; 
			break; 
            	}
            	else{//its a non terminal 
            		findFirst(symb , subResult) ; 
			addToResultSet(result , subResult) ; 
            		if(subResult['#']>0){//epsilon found.Continue traversing the production string
				if(productions[i][j+1]=='\0') result['#']++ ; 
            		}
            		else break;
            	}
            }
        }
	}
}

int main(void){
	cout<<"Enter number of productions : " ; cin>>P ;
	cout<<"Enter the productions : " ;
	for(int i =0 ;i <  P; i++) cin>>productions[i] ;
	for(int i =0 ;i < P ; i++){
        cout<< "First(" << productions[i][0]<< ") = "  ;
        char result[MAX] = {0} ; 
        findFirst(productions[i][0] , result) ;
        for(int k =0 ; k < MAX ; k++){
            if(result[k]>0) cout<<((char)k)<< " ";
        }
        cout<<endl;
	}
}


/*
TEST CASES:

1.

Enter number of productions : 3
Enter the productions : A->BC
B->#
C->c
First(A) = # c
First(B) = #
First(C) = c

2.

Enter number of productions : 4
Enter the productions : A->a
A->BCD
B->b
A->q
First(A) = a b q 
First(A) = a b q 
First(B) = b 
First(A) = a b q

-> redundancy here ; but it doesn't matter to you so...

3.

Enter number of productions : 4
Enter the productions : A->####a
A->a
A->bbbbA
A->x
First(A) = a b x
First(A) = a b x
First(A) = a b x
First(A) = a b x


4.

Enter number of productions : 6
Enter the productions : A->BCD
B->CD
C->#
C->c
A->aD
D->d
First(A) = # a c d 
First(B) = # c d 
First(C) = # c 
First(C) = # c 
First(A) = # a c d 
First(D) = d 

-> redundancy in number of productions. 
First (A)=d,a,c, should there be an # too?
Same for others.

*/
