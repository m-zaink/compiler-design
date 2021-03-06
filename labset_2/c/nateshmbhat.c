#include<stdio.h>
#include<stdbool.h>

typedef struct{
    int id , bt , pri , ar , wt , ta , alloted  ; 
    bool finished ;
}Process ;  

Process p[100] ; 
int N ;

void sortPriority(){
    for(int i =0 ; i < N ;i++){
        for(int j = 0 ;j < N-i-1 ; j++)
        {
            if(p[j].pri > p[j+1].pri)  {  //Swap 
                Process temp = p[j] ; 
                p[j] = p[j+1] ; 
                p[j+1] = temp ; 
            }
        }
    }
} 

void prioritySchedule(){
   int i, t = 0  ;  // time
   float avg_ta  = 0 , avg_wt  = 0; 
   sortPriority() ; 

   for( ; ; t++ ) // for every second choose the process to be alloted 1 second
    {
        int chosen = -1 ; 
        for(i =0 ;i < N ; i++){ 
            if(!p[i].finished && t>=p[i].ar) // for each process see if it has arrived alraedy
            {
                chosen = i ; break; 
            }
        }
        
        bool allDone = true ; 
        for(int i =0 ;i < N ;i++){
            if(!p[i].finished) { 
                allDone=false ; break ; 
            }
        }
        if(allDone) break ; 

        if(chosen<0) continue ; 

        p[chosen].alloted+=1 ; 
        if(p[chosen].alloted==p[chosen].bt){
            p[chosen].finished = true;
            p[chosen].ta = t+1-p[chosen].ar ;
            avg_ta+=p[chosen].ta ; 
            p[chosen].wt = p[chosen].ta - p[chosen].bt ; 
            avg_wt+=p[chosen].wt ; 
        }
    }

    // Display output
    for(int i= 0 ;i < N ; i++){
        printf("p%d = Wait Time = %d  , Turn around time = %d\n" , p[i].id , p[i].wt , p[i].ta) ; 
    }
    printf("Average wait time = %f , Average Turn around time = %f" , avg_wt/N , avg_ta/N) ; 
}


int main(void){
    printf("Enter number of processes : ") ; scanf("%d" , &N) ; 

    printf("Enter arrival , burst and priority : \n") ; 
    for(int i =0 ; i < N ; i++){
        Process temp ; 
        temp.wt = temp.ta =  temp.alloted = 0 ; temp.id = i ; temp.finished = false ; 
        scanf("%d %d %d" , &temp.ar , &temp.bt , &temp.pri) ; 
        p[i] = temp ; 
    }
    prioritySchedule() ; 
}

/*

Enter number of processes : 4
Enter arrival , burst and priority : 
1 3 5   
5 10 2
6 8 4
7 5 1

p3 = Wait Time = 0  , Turn around time = 5
p1 = Wait Time = 5  , Turn around time = 15
p2 = Wait Time = 14  , Turn around time = 22
p0 = Wait Time = 0  , Turn around time = 3
Average wait time = 4.750000 , Average Turn around time = 11.250000

*/