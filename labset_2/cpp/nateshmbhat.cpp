#include<iostream>
using namespace std ; 
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
            if(p[j].pri > p[j+1].pri) swap(p[j] , p[j+1]) ; 
        }
    }
} 

void prioritySchedule(){
   int i, t = 0  ;  // time
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
            p[chosen].wt = p[chosen].ta - p[chosen].bt ; 
        }
    }

    // Display output
    cout<<endl; 
    for(int i= 0 ;i < N ; i++){
        cout<<"p"<<p[i].id <<" = " << " Wait Time = " << p[i].wt <<" , Turn around time = " << p[i].ta <<endl; 
    }
}


int main(void){
    cout<<"Enter number of processes : " ; 
    cin>> N ;

    cout<<"Enter arrival , burst and priority : " <<endl; 
    for(int i =0 ; i < N ; i++){
        Process temp ; 
        temp.wt = temp.ta =  temp.alloted = 0 ; temp.id = i ; temp.finished = false ; 
        cin>>temp.ar >> temp.bt  >> temp.pri ; 
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

p3 =  Wait Time = 2 , Turn around time = 7
p1 =  Wait Time = 0 , Turn around time = 10
p2 =  Wait Time = 12 , Turn around time = 20
p0 =  Wait Time = -2 , Turn around time = 1
*/