#include<bits/stdc++.h>
#include<ctype.h>

using namespace std ; 

int main(void){

    char str[100]  ; 
    int cur =0 ; 
    cout<< " Enter string : " ; cin.getline(str, 100) ; 
    
    for(int i =0 ; str[i]  ; i++ )
    {
       char c = str[i] ;  
       switch(cur){
            case 0 : 
                if(c=='a') cur = 1;
                else cur= 8 ; 
                break ;
            case 1 : 
                if(c=='a') cur = 2 ;
                else if(c=='b') cur = 3; 
                else cur =8 ;
                break; 
            case 2 : 
                if(c=='b') cur = 6 ; 
                else if(c=='a') cur = 2 ; 
                else cur = 8 ; 
                break; 
            case 3 : 
                if(c=='b')cur = 5 ;
                else cur = 8 ;
                break; 
            case 5:
                if(c=='b') cur = 6  ;
                else cur = 8 ; 
       }
    }
    if(cur == 0 || cur == 1 || cur == 2) cout<<"\nString recognized under : a* " ; 
    if(cur == 3 || cur == 6 ) cout<<"\nString recognized under : a*b+ " ; 
    if(cur == 5 ) cout<<"\nString recognized under : abb " ; 
    if(cur==8) cout<<"\nInvalid String ! " ; 
}