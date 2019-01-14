//Author : karanpratap
//Program : Preemptive priority scheduling
//Sample output at end of program

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 20

/*
A structure which represents a process identified by its pid and 
having attributes arrival time(at), waiting time(wt),burst time(bt),prioroty. 
finish is a boolean which indicates that a process is finished once 
*/

struct Process{
	int pid;
	int at;
	int bt;
	int priority;
	bool finish;
};

//function prototypes
void sort(struct Process[],int);
void swap(struct Process*,struct Process*);
void sortpid(struct Process proc[], int n,int[],int[]); 

//a function to swap 2 integers
void swaparr(int* a,int*b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

/*
The Preemptive priority scheduling function
Input: An array of struct Process type,an integer denoting the number of processes
Output: The table consisting of information about individual processes and at the end
		the average waiting time and the average turnaround time for all the processes
*/

void prior(struct Process proc[],int n){
	int ex[n];
	int wt[n],tat[n];
	float total_wt=0.0,total_tat=0.0;

	int time=0,i;
	for(i=0;i<n;i++)
		ex[i]=0;
	for(;;time++){
		for(i=0;i<n;i++){
			if(proc[i].at<=time && !(proc[i].finish)){
				ex[i]++;
				break;
			}
		}
		if(ex[i]==proc[i].bt){
			proc[i].finish=true;
			tat[i]=time+1-proc[i].at;
			wt[i]=tat[i]-proc[i].bt;
			total_tat+=tat[i];
			total_wt+=wt[i];
		}
		if(i==n && time!=0)
			break;
	}
	sortpid(proc,n,wt,tat);
	printf("\nProcesses  Arrival Time  Burst Time  Priority  Waiting time  Turn Around Time\n");
	for(i=0;i<n;i++)
		printf("   %2d           %2d          %2d        %2d         %2d              %2d\n",proc[i].pid,proc[i].at,proc[i].bt,proc[i].priority,wt[i],tat[i]);
	printf("\nAvg Waiting time=%f\nAvg TurnAround time=%f\n",total_wt/(float)n,total_tat/(float)n);
}

/*
Function to sort the processes and their waiting times and turn around times according 
to their respective pids.
*/

void sortpid(struct Process proc[], int n,int wt[],int tat[]) { 
   int i,j; 
   for(i=0;i<n-1;i++)       
		for(j=0;j<n-i-1;j++) 
			if(proc[j].pid>proc[j+1].pid){ 
				swap(&proc[j],&proc[j+1]); 
				swaparr(&wt[j],&wt[j+1]);
				swaparr(&tat[j],&tat[j+1]);
			}
} 

/*
Function to compare 2 process based on their priority. Returns true if the priority
of the first arguement process is greater than the second
*/

bool comparison(struct Process a,struct Process b){
	return (a.priority>b.priority);
}

//Function to swap 2 struct Process type objects
void swap(struct Process* a,struct Process* b){
	struct Process temp=*a;
	*a=*b;
	*b=temp;
}

//Function to sort(in the ascending order) the Processes array based on the priority
//using bubble sort
void sort(struct Process proc[], int n) { 
   int i,j; 
   for(i=0;i<n-1;i++)       
		for(j=0;j<n-i-1;j++) 
			if(comparison(proc[j],proc[j+1])) 
				swap(&proc[j],&proc[j+1]); 
} 

//main function:handles user inputs and function calls
int main(){
	int n,i,j;
	printf("\nEnter the number of processes:");
	scanf("%d",&n);
	struct Process proc[MAX];
	for(i=0;i<n;i++){
		printf("\nEnter the pid, arrival time,burst time and priority of process %d:",i+1);
		scanf("%d",&proc[i].pid);
		scanf("%d",&proc[i].at);
		scanf("%d",&proc[i].bt);
		scanf("%d",&proc[i].priority);
		proc[i].finish=false;
		fflush(stdin);
	}
	//struct Process proc[]={{0,1,3,2,false},{1,2,4,1,false},{2,1,2,3,false},{3,3,5,1,false},{4,2,1,4,false}};
	sort(proc,n);
	prior(proc,n);
	printf("\n");
	return 0;
}

/*
	SAMPLE OUTPUT
	=============

	Enter the number of processes:5

	Enter the pid, arrival time,burst time and priority of process 1:0 1 3 2
	
	Enter the pid, arrival time,burst time and priority of process 2:1 2 4 1 
	
	Enter the pid, arrival time,burst time and priority of process 3:2 1 2 3 
	
	Enter the pid, arrival time,burst time and priority of process 4:3 3 5 1

	Enter the pid, arrival time,burst time and priority of process 5:4 2 1 4

	Processes  Arrival Time  Burst Time  Priority  Waiting time  Turn Around Time
	    0            1           3         2          9              12
	    1            2           4         1          0               4
	    2            1           2         3         12              14
	    3            3           5         1          3               8
	    4            2           1         4         13              14

	Avg Waiting time=7.400000
	Avg TurnAround time=10.400000
*/
