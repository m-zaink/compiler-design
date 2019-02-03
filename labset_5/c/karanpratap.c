//author : karanpratap
//program : Contigious memory allocation - worst fit, best fit and first fit

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100

int noOfProcesses;		//a variable to store number of processes
int noOfMemoryBlocks;	//variable to store number of memory blocks available
int memory[MAX];		//array to store the sizes of all the memory blocks
int processes[MAX];		//array to store the sizes of all the processes
bool filled[MAX];		//an array to hold whether the memory block i is filled or not
int allocation[MAX];	//an array to store the final allocation status; index denotes the memory block number and the value is the process number
int count=0;			//no of processes that have be alloted a memory block


/*
A function to fill the allocation array using the worst fit algorithm
	In each iteration we find the highest space memory block available and check if the 
	memory block is 'NOT' already being used by another process and that the memory block
	is large enough to hold the process under consideration. Then we accordingly fill the 
	allocation array.
*/
void worstFit(){
	int max=0,i,j,max_index=0;
	for(i=0;i<noOfProcesses;i++){
		max=0;
		for(j=0;j<noOfMemoryBlocks;j++){
			if(!filled[j] && memory[j]>max){
				max=memory[j];
				max_index=j;
			}
		}
		if(max>=processes[i]){
			filled[max_index]=true;
			count++;
			allocation[max_index]=i;
		}	
	}
}

/*
A function to fill the allocation array using the best fit algorithm
	In each iteration we find the lowest space memory block available and check if the 
	memory block is 'NOT' already being used by another process and that the memory block
	is large enough to hold the process under consideration. Then we accordingly fill the 
	allocation array.
*/

void bestFit(){
	int min=9999,i,j,min_index=0;
	for(i=0;i<noOfProcesses;i++){
		min=9999;
		for(j=0;j<noOfMemoryBlocks;j++){
			if(!filled[j] && memory[j]<min && memory[j]>=processes[i]){
				min=memory[j];
				min_index=j;
			}
		}
		if(min>=processes[i]){
			filled[min_index]=true;
			count++;
			allocation[min_index]=i;
		}
	}
}

/*
A function to fill the allocation array using the first fit algorithm
	In each iteration we simply see if the next memory block is large enough to accomodate
	the process under consideration. If not, we move on to the next memory block.
*/

void firstFit(){
	printf("\nFIRST FIT\n");
	int i,j;
	for(i=0;i<noOfProcesses;i++){
		for(j=0;j<noOfMemoryBlocks;j++){
			if((processes[i]<=memory[j]) && !filled[j]){
				allocation[j]=i;
				filled[j]=true;
				count++;
				break;
			}
		}
	}
}

//A global variable 'count' stores the number of processes that have been allocated. If the
//value of count is equal to the total no of processes, then the solution is found. Else,
//there is no solution and we display the suitable message.

int main(){
	int i,ch;
	printf("Contiguous memory allocation:\n");
	printf("Enter the no of processes:");
	scanf("%d",&noOfProcesses);
	printf("\nEnter the no of memory blocks:");
	scanf("%d",&noOfMemoryBlocks);
	if(noOfMemoryBlocks<noOfProcesses){
		printf("\nImpossible condition. The number of processes must be less than or equal to the number of memory blocks.\n");
		exit(0);
	}
	printf("\nEnter the sizes of the processes:\n");
	for(i=0;i<noOfProcesses;i++){
		printf("\nProcess %d:",i+1);
		scanf("%d",&processes[i]);
		filled[i]=false;
	}
	printf("\nEnter the sizes of the memory blocks:\n");
	for(i=0;i<noOfMemoryBlocks;i++){
		printf("\nMemory block %d:",i+1);
		scanf("%d",&memory[i]);
	}
	printf("Processes and memory blocks read successfully...\nEnter the type of fit you want:\n 1.Worst fit 2.Best Fit 3.First fit\nEnter your choice:");
	scanf("%d",&ch);
	switch(ch){
		case 1:worstFit();
				break;
		case 2:bestFit();
				break;
		case 3:firstFit();
				break;
		default:printf("\nWrong choice");
	}

	if(count!=noOfProcesses){
		printf("\nSolution not possible for the given situation\n");
		exit(1);
	}

	for(i=0;i<noOfMemoryBlocks;i++){
		printf("\nMemory Block %d : ",i+1);
		if(filled[i])
			printf("Process %d",allocation[i]+1);
		else
			printf("Unalloted");
	}
	printf("\n");
	return 0;
}

/*

SAMPLE OUTPUT
=============

1. WORST FIT

	Contiguous memory allocation:
	Enter the no of processes:3

	Enter the no of memory blocks:5

	Enter the sizes of the processes:

	Process 1:1

	Process 2:4

	Process 3:2

	Enter the sizes of the memory blocks:

	Memory block 1:6

	Memory block 2:9

	Memory block 3:2

	Memory block 4:10

	Memory block 5:5
	Processes and memory blocks read successfully...
	Enter the type of fit you want:
	 1.Worst fit 2.Best Fit 3.First fit
	Enter your choice:1
	
	Memory Block 1 : Process 3
	Memory Block 2 : Process 2
	Memory Block 3 : Unalloted
	Memory Block 4 : Process 1
	Memory Block 5 : Unalloted

2. BEST FIT
	
	Contiguous memory allocation:
	Enter the no of processes:3

	Enter the no of memory blocks:5

	Enter the sizes of the processes:

	Process 1:2

	Process 2:4

	Process 3:1

	Enter the sizes of the memory blocks:

	Memory block 1:5

	Memory block 2:7

	Memory block 3:1

	Memory block 4:2
	
	Memory block 5:4
	Processes and memory blocks read successfully...
	Enter the type of fit you want:
 	1.Worst fit 2.Best Fit 3.First fit
	Enter your choice:2

	Memory Block 1 : Unalloted
	Memory Block 2 : Unalloted
	Memory Block 3 : Process 3
	Memory Block 4 : Process 1
	Memory Block 5 : Process 2

3. FIRST FIT
	
	Contiguous memory allocation:
	Enter the no of processes:3

	Enter the no of memory blocks:5

	Enter the sizes of the processes:
	
	Process 1:2

	Process 2:5

	Process 3:3

	Enter the sizes of the memory blocks:

	Memory block 1:9

	Memory block 2:4

	Memory block 3:5
	
	Memory block 4:4
	
	Memory block 5:2
	Processes and memory blocks read successfully...
	Enter the type of fit you want:
	 1.Worst fit 2.Best Fit 3.First fit
	Enter your choice:3
	
	FIRST FIT

	Memory Block 1 : Process 1
	Memory Block 2 : Process 3
	Memory Block 3 : Process 2
	Memory Block 4 : Unalloted
	Memory Block 5 : Unalloted

===========================================================================================
