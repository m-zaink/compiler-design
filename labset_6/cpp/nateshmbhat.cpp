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
		if(frames[i]==-1)continue ;  //empty frame
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
	int i ; 
	int frameCount =0 ; //goes till F-1 which indicates all pages except the last one gives the least used page .
	int pageToOccurance[SIZE]  ; //keeps track of number of occurances of each before from position till first and returns the first page which is found after all other pages in the frame are found when traversing from i=pos-1 till 0 .
	memset(pageToOccurance , -1 , SIZE) ;  

	for(i =pos-1 ; i>=0 ;i--){
		if(frameCount==F-1) break ;  //the page we are looking for is before i 
		if(findFrame(pages[i])!=-1){
			if(pageToOccurance[pages[i]]<0) //check if same number has occured before while traversing back through the page string and only consider that for framecount if it wasn't seen before.
			{
				pageToOccurance[pages[i]]++ ;  
				frameCount++ ; 
			}
		}
	}
	while(i>=0){
		int lru =findFrame(pages[i])  ; 
		if(lru>=0 && pageToOccurance[pages[i]]==-1) return lru ; 	
		i-- ; 
	}

	cout<<"LRU : Page Faults = " << pageFaults <<endl; 
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



int getLeastFrequentUsed(int pos ){
	// returns the frame index of frame which contains the page that's used the least number of times till now.

	int minvalue = INT_MAX , minpos = -1 ; 
	int pageCounts[SIZE] = {0} ; 

	for(int i =pos-1 ; i>=0 ; i--)pageCounts[pages[i]]+= 1 ;

	for(int i =pos-1 ; i>=0 ; i--){
		if(minvalue>=pageCounts[pages[i]] && findFrame(pages[i])!=-1){
			minvalue= pageCounts[pages[i]] ; 
			minpos = i ; 
		}
	}

	for(int i =0 ;i < F ; i++)
		if(pages[frames[i]]==pages[minpos]) return i ; 
}


void LFU(){

	int pageCounts[SIZE] = {};  //count of each page

	pageFaults= 0 ; 

	for(int i =0 ;i < P ; i++){
		int frame = findFrame(pages[i]) ; 				

		if(frame==-1){//page fault
			pageFaults++ ; 
			int selectedFrame = getEmptyFrame() ; 
			selectedFrame = selectedFrame>=0?selectedFrame : getLeastFrequentUsed(i  ) ; 
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



/*

Enter no of frames : 4

Enter no of pages : 13

Enter page numbers : 7 0 1 2 0 3 0 4 2 3 0 3 2
FIFO : Page Faults = 7
LRU page faults = 6


-----------------------------------------------------------------

Enter no of frames : 4

Enter no of pages : 22

Enter page numbers : 1 2 3 4 5 3 4 1 6 7 8 7 8 9 7 8 9 5 4 5 4 2
FIFO : Page Faults = 13
LRU page faults = 13
LFU : Page Faults = 16

*/