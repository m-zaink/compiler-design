//Author : karanpratap
//Program : Page Replacement Algorithms - FIFO, LRU, LFU

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100

//global variables
int noOfPages, slots, pages[MAX], container[MAX],faults=0, useIndex=0, lru[MAX], usageFrequency[MAX],lfuFifoIndex=0;

void displayContainer(){
	int i;
	for(i=0;i<slots;i++){
		if(container[i]!=-1)
			printf("%d ",container[i]);
		else
			printf("- ");
	}
}

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

int main(){
	int ch,i;
	printf("\nEnter the number of pages:");
	scanf("%d",&noOfPages);
	printf("\nEnter the values for the pages:");
	
	for(i=0;i<noOfPages;i++)
		scanf("%d",&pages[i]);
	
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
		usageFrequency[i]=-1;
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
			//pageReplacementLFU();
			break;
		default:printf("\nInvalid Choice!");
	}
	
	printf("\n\nTotal number of page faults: %d\n",faults);

	return 0;
}
