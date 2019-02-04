// Author  : nateshmbhat
// Program : Page replacement algorithm
#include<iostream> 
#include<iomanip> 
#include<cstring>
#include<math.h>
#include<cstdlib>

#define SIZE 100
#define INT_MAX 9999

using namespace std ; 

typedef struct
{
	int f, r;
	int data[100];
} Queue;


Queue queue = {-1, -1}; //main queue for FIFO
int frames[SIZE]  ; 
int F; //no of frames
int P; //no of pages
int pages[SIZE];
int pageFaults = 0; //no of page faults
int pageCounts[SIZE] ; 

void enqueue(int data)
{
	queue.data[++queue.r] = data;
	if (queue.f == -1)
		queue.f = 0;
}

int dequeue()
{
	if (queue.f == -1)
		return -1;
	int data = queue.data[queue.f];

	if (queue.f == queue.r)
	{
		queue.f = queue.r = -1;
	}
	else
		queue.f++;
	return data ; 
}

void printFrame(){
	for(int i= 0 ;i < F ; i++){
		cout<<pages[frames[i]] << " " ; 
	}
	cout<<endl; 
}

int findFrame(int page)
{
	// returns index of page in any frame of else -1 if not found(page fault)
	for (int i = 0; i < F; i++)
	{
		if (pages[frames[i]]== page)
			return i; //found at frame i
	}
	return -1;
}

int getEmptyFrame()
{
	// get the first empty frame .
	for (int i = 0; i < F; i++)
	{
		if (frames[i]<0)
			return i;
	}
	return -1 ; 
}


void FIFO()
{
	int page = 0;
	pageFaults= 0 ; 
	for (int p = 0; p < P; p++) //pages[p] is the current page considered . p is the pointer here
	{
		int page = pages[p] ; 
		int frame = findFrame(page) ; 
		if (frame == -1) //not found
		{
			pageFaults++ ; 
			int emptyFrame = getEmptyFrame() ; 
			int selectedFrame  = emptyFrame!=-1 ? emptyFrame : dequeue() ;  //selected frame to put the page. If any empty frame found initally use that else use the FIFO order for frames. 

			frames[selectedFrame] = p ; 
			enqueue(selectedFrame);
		}
	}
	cout<<"FIFO : Page Faults = " << pageFaults <<endl; 
}


int getLeastRecentPagesFrame(int pos)
{
	// returns the frame number which contains the page which is least recently used
	int pageToFrameTable[100] = { 0} ;
	int recentCount[100] = { 0 } ; 
	int leastUsed = INT_MAX ; //position of page in pages which is least recently used

	for(int i =0 ;i < F ; i++) 
		pageToFrameTable[pages[frames[i]]] = i+1 ;  // page to frame mapping

	for(int i =pos-1 ;i  >= 0  ; i--){
		if(pageToFrameTable[pages[i]]>0){ // if page present in a frame , then map its position in recentCount
			if(recentCount[pages[i]]==0)
			{
				leastUsed = min(leastUsed , i ) ; 
				recentCount[pages[pos]] = i+1 ; 
			}
		}
	}

	return pageToFrameTable[pages[leastUsed]] ; 
}



void LRU(){
	pageFaults= 0 ; 

	for(int i =0 ;i < P ; i++){
		int frame = findFrame(pages[i]) ; 				

		if(frame==-1){//page fault
			pageFaults++ ; 
			int selectedFrame = getEmptyFrame(); 
			selectedFrame = selectedFrame>=0?selectedFrame : getLeastRecentPagesFrame(i) ; 
			frames[selectedFrame] = i ; 
		}
	}	

	cout<<"LRU page faults = " << pageFaults<<endl ; 
}



int getLeastFrequentUsed(int pos){
	// returns the frame index of frame which contains the page that's used the least number of times till now.

	int minvalue = INT_MAX , minpos = -1 ; 
	memset(pageCounts , 0 , SIZE) ; 

	for(int i =pos-1 ; i>=0 ; i--){
		pageCounts[pages[i]]+= 1 ; 
		if(minvalue>pageCounts[pages[i]]){
			minvalue= pageCounts[pages[i]] ; 
			minpos = i ; 
		}
	}


	for(int i =0 ;i < F ; i++)
		if(pages[frames[i]]==pages[minpos]) return i ; 
}


void LFU(){

	pageFaults= 0 ; 

	for(int i =0 ;i < P ; i++){
		int frame = findFrame(pages[i]) ; 				

		if(frame==-1){//page fault
			pageFaults++ ; 
			int selectedFrame = getLeastFrequentUsed(i) ; 
			selectedFrame = selectedFrame>=0?selectedFrame : getLeastRecentPagesFrame(i) ; 
			frames[selectedFrame] = i ; 
		}
	}	
	cout<< "LFU : Page Faults = " << pageFaults <<endl; 
}



int main(void){
	cout<<"Enter no of frames : " ;  cin>>F ; 
	cout<<"\nEnter no of pages : " ;  cin>>P ; 
	cout<<"\nEnter page numbers : " ; 

	for(int i =0 ;i < P ; i++)
		cin>>pages[i] ; 

	memset(frames , -1 , SIZE) ; 
	FIFO() ; 
	memset(frames ,  -1 , SIZE) ; 
	LRU() ;
	memset(frames ,  -1 , SIZE) ; 
	LFU() ; 
}