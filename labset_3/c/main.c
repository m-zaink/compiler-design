//Author : nateshmbhat
//Program : Producer Consumer problem using semaphores

#include<stdio.h>
#include<stdlib.h>
#define max 3

int mutex = 1, full = 0 , empty = max ; 
int buffer[10] , p= 0 , c =0 ; 

void wait(int * s){
	//decrements the semaphore
	*s = *s-1 ; 
}

void signal(int * s){
	//increments the semaphore
	*s = *s +1 ; 
}


void producer(int data){
	if(mutex==0 || empty==0){ printf("-- Buffer Full -- \n") ; return ;} 
	wait(&mutex) ; 
	wait(&empty) ; 
		
	p = (p+1)%max ; 
	buffer[p] = data ; 
	printf("Produced : %d" , data) ; 

	signal(&mutex) ; 
	signal(&full) ; 
}

void consumer(){
	if(mutex==0 || full==0) { printf("-- Empty Buffer -- \n"); return ; }
	wait(&mutex) ; 
	wait(&full) ; 
	c= (c+1)%max ; 
	int data = buffer[c] ; 
	printf("\nConsumed : %d" , data) ; 
	signal(&mutex) ; 
	signal(&empty) ; 
}

int main(void){
	int ch , data ; 
	while(1){
		printf("\n\n1.Producer    2.Consumer    3.Exit  : ") ; 
		scanf("%d" , &ch) ; 
		switch(ch){

			case 1 :
				printf("Enter data : " ) ; 
				scanf("%d", &data) ; 
				producer(data)  ; break ; 
			case 2 : 
				consumer() ; 
				break ; 
			case 3:
			return ; 
		}

	}
}
