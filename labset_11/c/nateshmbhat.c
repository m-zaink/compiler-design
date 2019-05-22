 #include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int numofproduct,k= 0  ; 
char productionset[10][10],str[20];

void recursiveDescent(char p)
{
	int found = 0 , temp , i , j  ; 

	for(i =0 ;i < numofproduct ; i++ )
	{
		if(productionset[i][0]==p){
			temp = k ; 
			for(int j =3 ; productionset[i][j] ; j++){
				while(str[k]=='#')k++ ; 
				if(isupper(productionset[i][j])){
					recursiveDescent(productionset[i][j]) ; 
				}
				else if(productionset[i][j] == str[k]){
					k++ ; 
				}
				else if (productionset[i][j] == '#'){
					continue ; 
				}
				else{
					k = temp ; 
					break; 
				}
			}
		}
	}
}


int main(void)
{
	printf("Number of productions:");
	scanf("%d",&numofproduct);
	printf("Enter the productions , enter # for epsilon : \n");
	for(int i=0;i<numofproduct;i++)
		scanf("%s",productionset[i]);

	while(1){
		k = 0 ; 	
		printf("\nEnter the string : ");
		scanf("%s",str);

		recursiveDescent(productionset[0][0]);

		if(k==strlen(str))
			printf("\n Input string is valid");
		else
			printf("\n Invalid string !!!");
	}
}


/*


Number of productions:3
Enter the productions , enter # for epsilon : 
S--cAd
A--ab
A--a

Enter the string : cad

 Input string is valid
Enter the string : caad

 Invalid string !!!
Enter the string : cabd

 Input string is valid
Enter the string : cabdd

 Invalid string !!!
Enter the string : ^C


=====================================================================

Number of productions:8
Enter the productions , enter # for epsilon : 
S--ABCD
A--a
B--#
C--d
C--k
C--h
D--#
D--h

Enter the string : ad

 Input string is valid
Enter the string : adh

 Input string is valid
Enter the string : ahh

 Input string is valid
Enter the string : akh

 Input string is valid
Enter the string : a###h

 Input string is valid
Enter the string : a###hh

 Input string is valid
Enter the string : add

 Invalid string !!!
Enter the string : ad#h#

 Input string is valid
Enter the string : ^C--id


*/