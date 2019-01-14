#include<bits/stdc++.h>
using namespace std ; 

int P  ; //no of processes 
int M  ; //no of memory blocks
int psizes[100] ; //processes sizes 
int memory[100] ; //memory blocks each representing size of that block
int memoryCopy[100] ; //copy of memory
int allocation[100] ; //array of numbers whose position represents the process and value represents the memory block allocated



void display(){
	cout<<endl<<"Process\t\tSizes\t\tMemoryBlocks(-1 = not allocated)" <<endl <<"--------------------------------------"<<endl ;
	for(int i =0 ;i < P ; i++){
		printf("%d\t\t%d\t\t%d\n" , i , psizes[i] , allocation[i] ) ; 
	}	
	cout<<endl<<endl;  
}

void bestFit(){
	for(int p = 0 ; p < P ; p++){ // p process 
		int minblock = -1 , minSize = INT_MAX ;  //minblock is position of memoryblock

		for(int m =0 ; m <M ; m++ )	 // m memory block 
		{
			if(memory[m]>=psizes[p] &&  memory[m]<minSize)	
			{
				minblock = m ; minSize = memory[m] ; 
			}
		}
		allocation[p] = minblock ; 
		if(minblock>=0) memory[minblock]-=psizes[p] ;   // if allocatable allocate process
	}
	cout<<"Best Fit : " ; 
	display() ; 
}

void worstfit(){
for(int p = 0 ; p < P ; p++){ // p process 
		int maxblock = -1 , maxSize = INT_MIN ;  //maxblock is position of memoryblock

		for(int m =0 ; m <M ; m++ )	 // m memory block 
		{
			if(memory[m]>=psizes[p] &&  memory[m]>maxSize)	
			{
				maxblock= m ; maxSize = memory[m] ; 
			}
		}
		allocation[p] = maxblock ; 
		if(maxblock>=0) memory[maxblock]-=psizes[p] ;   // if allocatable allocate process
	}

	cout<<"Worst Fit : " ; 
	display() ; 
}


void firstFit(){
	for(int p = 0 ; p < P ; p++){ // p process 
		allocation[p] = -1 ; 
		for(int m =0 ; m <M ; m++ )	 // m memory block 
		{
			if(memory[m]>=psizes[p])
			{
				memory[m]-=psizes[p] ; 
				allocation[p] = m ; 
				break ; 	
			}
		}
	}
	cout<<"First Fit : " ; 
	display() ; 
}

void resetMemBlocks(){
	for(int i=0 ;i< M ; i++ ) memory[i] = memoryCopy[i] ; 
}


int main(void){
	cout<<"Enter no of processes : " ;  cin>> P ; 
	cout<<"\nEnter no of memory blocks : " ; cin>>M ; 
	cout<<"\nEnter process sizes : " ; 
	for(int i =0 ; i< P ; i++ ) cin>> psizes[i] ; 
	cout<<"\nEnter memory block sizes : " ; 
	for(int i =0 ; i< P ; i++ ){ cin>> memory[i] ;  memoryCopy[i] = memory[i] ;  } 

	bestFit() ; 
	resetMemBlocks() ; 

	worstfit() ; 
	resetMemBlocks() ;  

	firstFit() ; 
}



/*

Enter no of processes : 5

Enter no of memory blocks : 5

Enter process sizes : 70 5 10 3 6 

Enter memory block sizes : 10 20 50 5 100
Best Fit : 
Process		Sizes		MemoryBlocks(-1 = not allocated)
--------------------------------------
0		70		4
1		5		3
2		10		0
3		3		1
4		6		1


Worst Fit : 
Process		Sizes		MemoryBlocks(-1 = not allocated)
--------------------------------------
0		70		4
1		5		2
2		10		2
3		3		2
4		6		2


First Fit : 
Process		Sizes		MemoryBlocks(-1 = not allocated)
--------------------------------------
0		70		4
1		5		0
2		10		1
3		3		0
4		6		1

*/
