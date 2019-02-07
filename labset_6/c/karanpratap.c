//Author : karanpratap
//Program : Page Replacement Algorithms - FIFO, LRU, LFU

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100

//global variables
int noOfPages;					//A variable to store the number of page requests
int slots;						//A variable to store the number of slots in the memory
int pages[MAX];					//An array to store the values of the page requests
int container[MAX];				//An array to store the contents of the memory
int faults=0;					//A variable to keep track of the number of page faults
int useIndex=0;					//[for LRU] lower value of this variable implies that the variable was not recently used
int lru[MAX];					//[for LRU] An array to store use Indices for different memory blocks
int lfuElementCount=0;			//[for LFU] A dynamic variable to store the number of elements in the lfuLeastSet array (please refer lfuLeastSet array description)
bool lfuReplacementStatus[MAX];	//[for LFU] An array to store the visited status of a particular page request to aid in case of multiple elements in the lfuLeastSet array
int lfuLeastSet[MAX];			//[for LFU] An array to store the elements with minimum usage frequency for the current frame 
int usageFrequency[MAX];		//[for LFU] An array to store the frequency of all the page requests currently in the frame. When a page is replaced, its frequency is reset to 1

/*
A function to display the current status of the memory frame
	The container (frame) is currently initialized with value -1 for all slots
*/
void displayContainer(){
	int i;
	for(i=0;i<slots;i++){
		if(container[i]!=-1)
			printf("%d ",container[i]);
		else
			printf("- ");
	}
}

/*
[for LFU] A function to return the index of a particular page request value
	This function takes in a page request value and returns its corresponding index
	in the container. (-1 if not found)
*/
int indexInContainer(int value){
	int i;
	for(i=0;i<slots;i++)
		if(value==container[i])
			return i;
	return -1;
}

/*
[for LFU] A function to find the least frequently occuring page requests from the current status of the container
	This function first finds the minimum value for the frequency
	Then, all the page requests having this minimum frequency value are added to the lfuLeastSet Array
	The function returns the number of values added to the lfuLeastSet array; i.e number of page requests having the minimum usage frequencies
	->Note that there will always be at least one value which is added to the lfuLeastSet array
*/
int fillLfuLeastSet(){
	int min=9999,leastSetIndex=0,i;
	for(i=0;i<noOfPages;i++)
		lfuLeastSet[i]=-1;
	for(i=0;i<slots;i++){
		if(usageFrequency[i]<min){
			min=usageFrequency[i];
		}
	}
	for(i=0;i<slots;i++){
		if(usageFrequency[i]==min){
			lfuLeastSet[leastSetIndex]=container[i];
			leastSetIndex++;
		}
	}
	return leastSetIndex;
}

/*
[for LRU] A function to return the least element index from an array
	Used here for finding the least recently used element index from the current frame elements
*/
int least(int* data){
	int i,min=9999,index=0;
	for(i=0;i<slots;i++){
		if(data[i]<min){
			min=data[i];
			index=i;
		}
	}
	return index;
}

/*
[for LFU] A function to check whether a given value is present in the lfuLeastSet
	Returns true if the value is found; otherwise false
	->Note: This function comes into play when there are multiple elements in the lfuLeastSet array; In that case, FIFO is applied and the request which came first is selected for replacement
*/
bool foundInLfuLeastSet(int data){
	int i;
	for(i=0;i<lfuElementCount;i++){
		if(data==lfuLeastSet[i]){
			return true;
		}
	}
	return false;
}

/*
[for FIFO/LFU/LRU] A function to check whether the current page request is a hit or not
	Compares the page request value with those present in the memory frame (container)
	If a match is found, the index of that particular slot is returned (-1 on failure)
*/
int checkForHit(int page,int currentIndex){
	int flag=-1;
	int i;
	if(container[currentIndex]==-1)
		return -1;
	for(i=0;i<slots;i++){
		if(container[i]==page){
			flag=i;
			break;
		}
	}
	return flag;
}

/*
[for FIFO] Function to apply FIFO Page Replacement Algorithm
	*Check for a possible Hit;If yes, increment the usage Frequency of the hit page and move on to the next iteration;
	*Otherwise, replace the page at indexToReplace position with the current request, increment page fault and increment indexToReplace within the bounds of the container.
	*Display the container before moving on the next iteration
*/
void pageReplacementFIFO(){
	int indexToReplace=0,i;
	for(i=0;i<noOfPages;i++){
		if(checkForHit(pages[i],indexToReplace)!=-1){
			printf("\nHit!");
			continue;
		}
		printf("\nFault: ");
		faults++;
		container[indexToReplace]=pages[i];
		indexToReplace=(indexToReplace+1)%slots;
		displayContainer();
	}
}

/*
[for LRU] Function to apply LRU Page Replacement Algorithm
	*Check for a possible Hit;If yes, increment the usage Frequency of the hit page and move on to the next iteration;
	*Otherwise, Check whether there are any slots empty in the container
		--If there are, insert the page request value there, increment page faults, increment its usage frequency and display the current status of the container before moving on to the next iteration
		--Otherwise,We need to find a page to be replaced in the container; find the least Recently used page out of the current elements in the container. Replace the resultant of the previous operation and reset its usage Frequency to 1, increment page faults. Display the current contents of the container before moving on to the next Iteration

*/
void pageReplacementLRU(){
	int indexToReplace=0,i,hitIndex;
	for(i=0;i<noOfPages;i++){
		hitIndex=checkForHit(pages[i],indexToReplace);
		if(hitIndex!=-1){
			printf("\nHit");
			indexToReplace++;
			lru[hitIndex]=useIndex;
			useIndex++;
			continue;
		}
		printf("\nFault: ");
		faults++;
		if(lru[i%slots]==-1){
			container[i]=pages[i];
			lru[i]=useIndex;
			useIndex++;
			displayContainer();
			continue;
		}
		container[least(lru)]=pages[i];
		lru[least(lru)]=useIndex;
		useIndex++;
		displayContainer();
	}	
}

/*
[for LFU] Function to apply LFU Page Replacement Algorithm
	*Check for a possible Hit;If yes, increment the usage Frequency of the hit page and move on to the next iteration;
	*Otherwise, Check whether there are any slots empty in the container
		--If there are, insert the page request value there, increment page fault, increment usage frequency and display the current status of the container before moving on to the next iteration
		--Otherwise,
			==We need to find a page to be replaced in the container; find the least frequently used page out of the current elements in the container. If the result is multiple elements, then apply FIFO on the page requests to find the page which was the first one we encountered and mark it as visited by unsetting its lfuReplacementStatus. Replace the resultant of the previous operation and reset its usage Frequency to 1, increment page faults. Display the current contents of the container before moving on to the next Iteration
*/
void pageReplacementLFU(){
	int indexToReplace=0,i,hitIndex,target,j,targetIndex;
	for(i=0;i<noOfPages;i++){
		hitIndex=checkForHit(pages[i],indexToReplace);
		if(hitIndex!=-1){
			printf("\n[%d]Hit",pages[i]);
			indexToReplace++;
			usageFrequency[hitIndex]++;
			continue;
		} 
		printf("\n[%d]Fault: ",pages[i]);
		faults++;
		if(usageFrequency[i%slots]==0){
			container[i]=pages[i];
			usageFrequency[i]++;
			displayContainer();
			continue;
		}
		lfuElementCount=fillLfuLeastSet();
		if(lfuElementCount==1){
			target=lfuLeastSet[0];
		}
		else{
			for(j=0;j<i;j++){
				if(foundInLfuLeastSet(pages[j]) && lfuReplacementStatus[j]){
					target=pages[j];
					lfuReplacementStatus[j]=false;
					break;
				}
			}
		}
		targetIndex=indexInContainer(target);
		container[targetIndex]=pages[i];
		usageFrequency[targetIndex]=1;
		displayContainer();
	}
}

/*
Main function:
	Takes in the number of page requests, the values for them, the number of slots in the container (Memory frame), and finally the choice of the Replacement Algorithm to be applied.
	Based on the choice, the respective function is called and finally the number of page faults is displayed before termination.
	*ALSO, checks if the number of slots in the container is greater than the number of page requests, and displays suitable message.
*/
int main(){
	int ch,i;
	printf("\nEnter the number of pages:");
	scanf("%d",&noOfPages);
	printf("\nEnter the values for the pages:");
	
	for(i=0;i<noOfPages;i++){
		scanf("%d",&pages[i]);
		lfuReplacementStatus[i]=true;
	}

	printf("\nEnter the memory capacity(No of slots):");
	scanf("%d",&slots);	
	
	printf("\n\n1. FIFO 2. LRU 3. LFU\nSelect the page replacement technique to be used: ");
	scanf("%d",&ch);

	if(noOfPages<=slots){
		printf("\nThe memory capacity is greater than or equal to the no of pages.\nThus number of faults = %d (No of pages)\n",noOfPages); 
		exit(1);
	}
	
	for(i=0;i<slots;i++){
		container[i]=-1;
		lru[i]=-1;
		usageFrequency[i]=0;
	}
	switch(ch){
		case 1:printf("\nFIFO Page replacement:\n");
			pageReplacementFIFO();
			break;
		case 2:printf("\nLRU Page replacement:\n");
			pageReplacementLRU();
			break;
		case 3:
			printf("\nLFU Page replacement:\n");
			pageReplacementLFU();
			break;
		default:printf("\nInvalid Choice!");
	}
	
	printf("\n\nTotal number of page faults: %d\n",faults);

	return 0;
}

/*
SAMPLE OUTPUT
=============

FIFO
----

	Enter the number of pages:15

	Enter the values for the pages:7 0 1 2 0 3 0 4 2 3 0 3 2 1 2

	Enter the memory capacity(No of slots):3


	1. FIFO 2. LRU 3. LFU
	Select the page replacement technique to be used: 1
	
	FIFO Page replacement:

	Fault: 7 - - 
	Fault: 7 0 - 
	Fault: 7 0 1 
	Fault: 2 0 1 
	Hit!
	Fault: 2 3 1 
	Fault: 2 3 0 
	Fault: 4 3 0 
	Fault: 4 2 0 
	Fault: 4 2 3 
	Fault: 0 2 3 
	Hit!
	Hit!
	Fault: 0 1 3 
	Fault: 0 1 2 

	Total number of page faults: 12


LRU
---

	Enter the number of pages:15

	Enter the values for the pages:7 0 1 2 0 3 0 4 2 3 0 3 2 1 2

	Enter the memory capacity(No of slots):4
	
	
	1. FIFO 2. LRU 3. LFU
	Select the page replacement technique to be used: 2

	LRU Page replacement:

	Fault: 7 - - - 
	Fault: 7 0 - - 
	Fault: 7 0 1 - 
	Fault: 7 0 1 2 
	Hit
	Fault: 3 0 1 2 
	Hit
	Fault: 3 0 4 2 
	Hit
	Hit
	Hit
	Hit
	Hit
	Fault: 3 0 1 2 
	Hit

	Total number of page faults: 7


LFU
---

	Enter the number of pages:15

	Enter the values for the pages:7 0 1 2 0 3 0 4 2 3 0 3 2 1 2

	Enter the memory capacity(No of slots):3


	1. FIFO 2. LRU 3. LFU
	Select the page replacement technique to be used: 3

	LFU Page replacement:

	[7]Fault: 7 - - 
	[0]Fault: 7 0 - 
	[1]Fault: 7 0 1 
	[2]Fault: 2 0 1 
	[0]Hit
	[3]Fault: 2 0 3 
	[0]Hit
	[4]Fault: 4 0 3 
	[2]Fault: 4 0 2 
	[3]Fault: 3 0 2 
	[0]Hit
	[3]Hit
	[2]Hit
	[1]Fault: 3 0 1 
	[2]Fault: 3 0 2 

	Total number of page faults: 10


SPECIAL CASE (No of pages <= No of slots in the container)
----------------------------------------------------------

	Enter the number of pages:15

	Enter the values for the pages:7 0 1 2 0 3 0 4 2 3 0 3 2 1 2

	Enter the memory capacity(No of slots):20


	1. FIFO 2. LRU 3. LFU
	Select the page replacement technique to be used: 2

	The memory capacity is greater than or equal to the no of pages.
	Thus number of faults = 15 (No of pages)

*/
