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


Process processes[100] ;  //Array of all processes
int n ;  //Number of processes

int findTotalBurstTime(){
	int sum = 0 , i =0 ; 
	for(i =0 ; i < n ; i++) sum+=processes[i].burstTime ; 
	return sum ;
}

int sortCompare(const void * p ,const void * q){
	return ((Process *)p)->arrivalTime - ((Process * )q)->arrivalTime ; 
}


bool areAllScheduled(){
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

	while(!areAllScheduled()){ //loop until all processes are scheduled
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
	for( i =0 ;i < n ; i++ )
	{
		printf("\n  Enter Process Number, BurstTime , ArrivalTime , Priority : ", i ) ; 
		scanf("%d %d %d %d" ,&processes[i].id , &processes[i].burstTime , &processes[i].arrivalTime , &processes[i].priority) ; 
		processes[i].remainingTime = processes[i].burstTime ; 
		processes[i].scheduled = false ; 
	}
}


int main(void){
	readProcessData() ; 
	scheduleProcesses() ; 
}