//Author : nateshmbhat
//Program : FCFS scheduling

#include<stdio.h>
#include<stdlib.h>
#define max(a,b) a<b?a:b

typedef struct{
	int pnum ;
	float wait ,bt ,  ta , arrival ; 
}Process ; 


int size ; 
Process * P ; 


float findWait(Process * P){
	int time = 0 ,i  ;float avg = 0 ;
	time = P[0].arrival ; // Sets the time to the arrival of first process incase if it doesn't start from 0 

	for(i =0 ;i < size ; i++){
		P[i].wait = time-P[i].arrival ; 
		if(P[i].wait<0) P[i].wait = 0 ; 
		avg+=P[i].wait ; 
		time+=P[i].bt;
		if(i+1 < size && time < P[i+1].arrival){
			time = P[i+1].arrival ; 
		}
	}
	avg/=size ; 
	return avg ; 
}

float findTurn(Process * P){
	int i,  time =0 ; float avg = 0  ; 
	for(i =0 ;i < size ; i++){
		time=P[i].bt+P[i].wait ; 
		avg+=time ; 
		P[i].ta=time ; 
	}
	return avg/(float)size ; 
}


void sort(Process * P){
	int i, j  ; 
	for( i =0 ;i<size ; i++){
		for(j =0 ;j<size-i-1 ; j++){
			if(P[j].arrival >P[j+1].arrival){
				Process temp = P[j] ; 
				P[j] = P[j+1] ; 	
				P[j+1] = temp ;
			}
		}
	}
}

void takeinput(Process * P){
	int i =0 ;   
	printf("Enter process number , burst time and arrival times  : \n" ) ; 
	for(i =0 ;i < size ; i++){
		scanf("%d %f %f" , &P[i].pnum , &P[i].bt , &P[i].arrival ) ; 
	}
	sort(P) ; 
}


void main(){
	int i; 
	printf("Enter no of processes : " ) ;scanf("%d" , &size) ; 
	Process * P = (Process *)malloc(sizeof(Process)* size) ; 
	takeinput(P) ; 
	printf("Average wait time : %.2f " ,  findWait(P)) ; 
	printf("Average Turn around time : %.2f \n" , findTurn(P)) ; 
	for(i =0 ;i <size ; i++){
		printf(" Process %d : wait time =%.2f , TA time = %.2f \n" , P[i].pnum ,P[i].wait  , P[i].ta) ; 
	}
}



/*

Enter no of processes : 3
Enter process number , burst time and arrival times  : 
0 1 3
0 2 2
0 3 1
Average wait time : 1.67 Average Turn around time : 3.67 
 Process 0 : wait time =0.00 , TA time = 3.00 
 Process 0 : wait time =2.00 , TA time = 4.00 
 Process 0 : wait time =3.00 , TA time = 4.00 


-------------------------------------------------------------

Enter no of processes : 3
Enter process number , burst time and arrival times  : 
0 1 1
1 1 2
2 1 3
Average wait time : 0.00 Average Turn around time : 1.00 
 Process 0 : wait time =0.00 , TA time = 1.00 
 Process 1 : wait time =0.00 , TA time = 1.00 
 Process 2 : wait time =0.00 , TA time = 1.00 


-------------------------------------------------------------


Enter no of processes : 3
Enter process number , burst time and arrival times  : 
0 2 0
1 4 3
2 5 5
Average wait time : 0.67 Average Turn around time : 4.33 
 Process 0 : wait time =0.00 , TA time = 2.00 
 Process 1 : wait time =0.00 , TA time = 4.00 
 Process 2 : wait time =2.00 , TA time = 7.00


 
*/
