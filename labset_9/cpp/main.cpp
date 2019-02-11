#include<bits/stdc++.h>
#include<ctype.h>
#define MAX 256
using namespace std ;

int P ; //no of productions
char productions[MAX][MAX];

void findFirst(char c , char result[] ){
	if(islower(c)){ result[c++] ; return ; }
	char subResult[MAX] ; 
	bool epsilonFlag = false ; 

	for(int i =0 ;i < P ; i++){// traverse through all the productions to find the production which matches the Non terminal 'c'
        if(productions[i][0]==c){
            for(int j =3 ; productions[i][j] ; j++){
            	char symb = productions[i][j] ;
            	if(islower(symb)){
					result[symb]++ ; 
					break; 
            	}
            	else{//its a non terminal 
            		findFirst(c , subResult) ; 
            		for(int k  = 0 ; K<MAX ; k++){
            			if(subResult[k]>0 && k!='#') result[k]++  ; 
            		}
            		if(subResult['#']>0){//epsilon found.
            			continue ; 
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

	for(int i =0 ;i <  P; i++){
		cin>>productions[i] ;
	}

	for(int i =0 ;i < P ; i++){
        cout<< "First(" << productions[i][0]<< ") = "  ;
        char result[MAX] ; 
        findFirst(productions[i][0] , result) ;

        for(int k =0 ; k < MAX ; k++){
            if(result[k]>0)
                cout<<((char)k)<< " ";
        }
        cout<<endl;
	}
}
