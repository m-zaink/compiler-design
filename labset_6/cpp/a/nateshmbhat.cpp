// Author  : nateshmbhat
// Program : Page replacement algorithm

#include<bits/stdc++.h>

using namespace std;

typedef struct{
	int f , r ; 
	int data[100];
}Queue; 

Queue queue ={-1,-1} ;  //main queue

void enqueue(Queue* q , int data ){
	q->data[q->r++] = data ; 	
	if(q->f==-1) q->f = 0 ; 
}

int dequeue(Queue* q ){
	if(q->f==-1) return ; 
	int data = q->data[q->f] ; 

	if(q->f ==q->r){
		q->f = q->r = -1 ; 
	}
	else q->f++ ; 
}


int frameMatrix[100][100] ;
int F ; //no of frames 
int P ; //no of pages 
int pages[100] ;
int pageFaults = 0 ;  //no of page faults 


void FIFO(){
	int pos = -1 ; // keeps track of the pages in FIFO order 
	for(int p =0 ;p < P ; p++){
		pos = -1 ; 
		for(int f = 0 ; f< F ; f++){
			i
		}
	}
}


void LRU(){

}

void LFU(){

}


int main(void){
	cout<<"Enter no of frames : " ;  cin>>F ; 
	cout<<"\nEnter no of pages : " ;  cin>>P ; 
	cout<<"\nEnter page numbers : " ; 
	for(int i =0 ;i < P ; i++)
		cin>>pages[i] ; 
}