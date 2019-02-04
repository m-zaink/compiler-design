#include<bits/stdc++.h>
#include<ctype.h>

using namespace std ; 

int main(void){
	char str[100] ; 
	cout<<"\nEnter the identifier string : "  ; cin>>str ; 	
	bool valid = true ; 

	for(int i =0 ; str[i] ; i++){
		if(i==0 && !(isalpha(str[i]) || str[i]=='_' ))
			 valid = false ; 
		else{

			if (!(isalnum(str[i])|| str[i]=='_'))
				valid = false ; 
		}
	}
	if(valid)cout<<"\nValid Identifier" ; 
	else cout<<"\nInvalid Identifier" ; 
}