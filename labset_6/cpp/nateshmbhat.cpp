// Author  : nateshmbhat
// Program : Page replacement algorithm
#include<iostream> 
#include<iomanip> 
#include<cstring>
#define SIZE 100
#define INT_MAX 9999
using namespace std ; 

int frames[SIZE]  ;  //Frames array which contains the index of the page which resides in each frame
int F; //no of frames
int P; //no of pages
int pages[SIZE];
int pageFaults = 0; //no of page faults

int findFrame(int page)
{ // returns index of page in any frame of else -1 if not found(page fault)
	for (int i = 0; i < F; i++)
	{
		if(frames[i]==-1)continue ;  //empty frame
		if (pages[frames[i]]== page)
			return i; //found at frame i
	}
	return -1;
}

int getEmptyFrame()
{ // get the first empty frame .
	for (int i = 0; i < F; i++)
	{
		if (frames[i]<0) return i;
	}
	return -1 ; 
}

int getLeastRecentPagesFrame(int pos)
{
	// returns the frame number which contains the page which is least recently used
	int i ; 
	int frameCount =0 ; //goes till F-1 which indicates all pages except the last one gives the least used page .
	int pageToOccurance[SIZE]  ; //keeps track of number of occurances of each before from position till first and returns the first page which is found after all other pages in the frame are found when traversing from i=pos-1 till 0 .
	memset(pageToOccurance , -1 , SIZE) ;  

	for(i =pos-1 ; i>=0 ;i--){ //Traverse from pos-1 till we see all the pages that are present in the frame except the last page which is the LRU page
		if(frameCount==F-1) break ;  //the page we are looking for is left of i.
		if(findFrame(pages[i])!=-1){
			if(pageToOccurance[pages[i]]<0) //check if same number has occured before while traversing back through the page string and only consider that for framecount if it wasn't seen before.
			{
				pageToOccurance[pages[i]]++ ;  
				frameCount++ ; 
			}
		}
	}
	while(i>=0){ //search for the LRU page which lies to the left of i 
		int lru =findFrame(pages[i])  ; 
		if(lru>=0 && pageToOccurance[pages[i]]==-1) return lru ; 	
		i-- ; 
	}
	cout<<"LRU : Page Faults = " << pageFaults <<endl; 
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


int main(void){
	int ch , queueRear , queueFront , queue[100] ; 
	cout<<"Enter no of frames : " ;  cin>>F ; 
	cout<<"\nEnter no of pages : " ;  cin>>P ; 
	cout<<"\nEnter page numbers : " ; 
	for(int i =0 ;i < P ; i++)
		cin>>pages[i] ; 

	while(1){
		cout<<"\n1.FIFO\t2.LRU\t3.LFU : "  ; cin>>ch ; 
		memset(frames , -1 , SIZE * sizeof(int)) ;  // set all elements of frames to -1 which indicates all frames are empty
		pageFaults= 0 , queueRear =-1 , queueFront = 0  ;

		for(int i =0 ;i < P ; i++){
			int frame = findFrame(pages[i]) ;
			if(frame==-1){//page fault happened
				pageFaults++ ; 
				int selectedFrame = getEmptyFrame() ; 
				if(selectedFrame <0 ){ // no empty frame exists
					if(ch==1){
						selectedFrame =  queue[queueFront++]  ;  //get front of queue which has frame number correposnding to FIFO
						frames[selectedFrame] = i ; 
					}

					if(ch==2) selectedFrame = getLeastRecentPagesFrame(i) ; //LRU
					if(ch==3) selectedFrame =  getLeastFrequentUsed(i) ;  // LFU
				} 

				queue[++queueRear]= selectedFrame; //insert frame number in the queue(used in FIFO algorithm)

				frames[selectedFrame] = i ; 
			}
		}
		cout<< "Page Faults = " << pageFaults <<endl; 
	}
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