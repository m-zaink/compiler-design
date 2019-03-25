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
            	if(isupper(symb)){//its a non terminal 
            		findFirst(symb , subResult) ; 
					addToResultSet(result , subResult) ; 
            		if(subResult['#']>0 && productions[i][j+1]=='\0') {//epsilon found.Continue traversing the production string
						result['#']++ ; 
            		}
            		else break;
            	}
				else{ //First(X) found for current production . add it to result . Break from traversing the string and go for the next production
					result[symb]++ ; 
					break; 
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