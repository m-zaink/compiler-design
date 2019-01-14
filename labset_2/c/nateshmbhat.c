//Author : nateshmbhat
//Program : Preemptive priority scheduling
//Time : O(n^2)

#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<stdbool.h>
#define INT_MAX 230322

typedef struct{
	int arrivalTime, id , waitTime , burstTime , priority , remainingTime ; 
	bool scheduled ; 
}Process ; 

typedef struct{
	int current , next ; 
} ProcessPair ; 


Process processes[100] ; 
int n ; 

int sortCompare(const void * p ,const void * q){
	//This function is the sort utility for Process array to be later used in.
	return ((Process *)p)->arrivalTime - ((Process * )q)->arrivalTime ; 
}


bool areAllProcessesScheduled(){
	int i =0 ;
	for(i =0 ; i < n ;i++) if(!processes[i].scheduled)return false ;
	return true ; 
}


ProcessPair getNextProcessToExecute(int timeElapsed){
	// returns a pair of processes , the current process to be executed and the next possible process with higher priority which can preempt the current process or -1 if no such process exists .

	int i =0 ; int minPr = INT_MAX, current , nextProcess= -1 ;

	for(i=0 ;i < n ; i++){
		if(!processes[i].scheduled && processes[i].arrivalTime <= timeElapsed &&
		 processes[i].priority<minPr ){
			minPr = processes[i].priority ; 	
			current = i ; 
		}
	}

	//Find the next processes to be scheduled after the process processes[current]
	//Since array is sorted on Arrivaltime , traversing from current index till end will be enough to search for the new process

	for(i=current ; i < n ; i++){
		if(!processes[i].scheduled && 
			current!=i &&
			processes[i].priority < minPr &&
			processes[i].arrivalTime > timeElapsed
			){
			nextProcess= i ; 
			break ; 
		}	
	}

	ProcessPair pair = {current , nextProcess} ; 
	return pair ; 
}


void updateWaitTimes(int currentProcess, int currentProcessTime){
	int i =0 ;
	for(i=0 ;i < n ;i++){
		// The current process doesn't wait when it is scheduled. So exclude it.
		if(i!=currentProcess && !processes[i].scheduled){
			processes[i].waitTime+= currentProcessTime ; 
		}
	}	
}


void displayScheduleInfo(int order[100], int number){
	int i =0,p ; 
	double avgWait = 0 , avgTA = 0 ; 
	printf("\nGantt chart is as follows : \n\n") ;
	for(int i =0 ;i < number ; i++){
		printf("P.id=%d\t" , processes[order[i]].id) ; 
	}
	puts("\n") ;
	for(i = 0 ; i< n ; i++){
		Process p  = processes[i] ; 
		avgWait+= p.waitTime ; 
		avgTA+= p.waitTime+p.burstTime ; 
		printf("Process %d : WaitTime = %d , TurnAroundTime = %d .\n" , p.id, p.waitTime , p.waitTime+p.burstTime ) ; 
	}
	printf("\nAverage TurnAroundTime = %.2f   :  Average WaitTime = %.2f\n", avgWait/n , avgTA/n ); 
}


void scheduleProcesses(){
	// Sort processes based on arrival Time {
	qsort(processes , n , sizeof(processes[0]) , sortCompare) ; 
	// }

	int time = 0 ; 
	int order[100] , orderPointer =0 ; //This is the array which holds the gantt chart

	while(!areAllProcessesScheduled())
	{ 
		//loop until all processes are scheduled
		ProcessPair pair = getNextProcessToExecute(time) ; 

		int current = pair.current, next = pair.next; 
		int currentProcessTime = 0 ; 

		if(next!=-1){ // There is such a process which will preempt the current process
			processes[current].remainingTime -= processes[next].arrivalTime - time  ; 
			currentProcessTime=processes[next].arrivalTime- time ; 
		}

		else{ //No such process give full cpu time to the current processs
			currentProcessTime = processes[current].remainingTime ; 
			processes[current].remainingTime = 0 ; 
		}

		time+= currentProcessTime ; 

		if(processes[current].remainingTime==0) 
			processes[current].scheduled = true ;
		order[orderPointer++] = current ; 

		updateWaitTimes(current, currentProcessTime) ; 
	}

	displayScheduleInfo(order,orderPointer) ; 
}

void readProcessData(){
	// Take Input for Processes
	int i ; 
	printf("\nEnter number of processes : ") ; 
	scanf("%d", &n) ;  // n is a global variable representing total number of processes.

	printf("\nEnter Process Number, BurstTime , ArrivalTime , Priority : \n", i ) ; 
	for( i =0 ;i < n ; i++ )
	{
		scanf("%d %d %d %d" ,&processes[i].id , &processes[i].burstTime , &processes[i].arrivalTime , &processes[i].priority) ; 
		processes[i].remainingTime = processes[i].burstTime ; 
		processes[i].scheduled = false ; 
	}
}


int main(void){
	readProcessData() ; 
	scheduleProcesses() ; 
}


/*
Enter number of processes : 4

Enter Process Number, BurstTime , ArrivalTime , Priority :
1 5 6 2
2 6 4 0
3 8 0 1
4 10 8 4

Gantt chart is as follows :

P.id=3  P.id=2  P.id=3  P.id=1  P.id=4

Process 3 : WaitTime = 6 , TurnAroundTime = 14 .
Process 2 : WaitTime = 4 , TurnAroundTime = 10 .
Process 1 : WaitTime = 14 , TurnAroundTime = 19 .
Process 4 : WaitTime = 19 , TurnAroundTime = 29 .

Average TurnAroundTime = 10.75   :  Average WaitTime = 18.00


----------------


Enter number of processes : 3

Enter Process Number, BurstTime , ArrivalTime , Priority :
1 10 3 0
2 4  0 2
3 2  2 1

Gantt chart is as follows :

P.id=2  P.id=3  P.id=1  P.id=3  P.id=2

Process 2 : WaitTime = 12 , TurnAroundTime = 16 .
Process 3 : WaitTime = 12 , TurnAroundTime = 14 .
Process 1 : WaitTime = 3 , TurnAroundTime = 13 .

Average TurnAroundTime = 9.00   :  Average WaitTime = 14.33

*/