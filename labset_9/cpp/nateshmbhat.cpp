//Program : Find First(X) where X is a non terminal for a Grammar given a set of productions
//Author : nateshmbhat
#include<bits/stdc++.h>
using namespace std ; 
#define MAX 256
int P ; 
char productions[100][100] ; 

void addToResultSet(char * dest , char * src){
    for(int i=0 ;i < MAX ; i++){
        if(i=='#') continue ; 
        dest[i]+=src[i] ; 
    }
}

void findFirst(char c , char * result){
    if(!isupper(c)){
        result[c]++ ; return ; 
    }
    for(int i =0 ;i < P ; i++){
        if(c==productions[i][0]){
            for(int j = 3 ; productions[i][j] ; j++){
                char k = productions[i][j] ; 
                
                if(isupper(k)){
                    char subResult[MAX]={0} ; 
                    findFirst(k , subResult) ; 
                    addToResultSet(result , subResult) ; 
                    if(subResult['#']>0 && productions[i][j+1]==0){
                        result['#']++ ; 
                    }
                    else if(subResult['#']==0) break ; 
                }
                else{
                    if(k=='#' && strlen(productions[i]+j)!=1) continue ; 
                    result[k]++ ; 
                    break ; 
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
First(A) = c
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
First(A) = a c d 
First(B) = c d 
First(C) = # c 
First(C) = # c 
First(A) = a c d 
First(D) = d 

*/