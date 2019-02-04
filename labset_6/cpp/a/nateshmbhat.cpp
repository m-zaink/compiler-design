// Author  : nateshmbhat
// Program : Page replacement algorithm

#include<iostream>
#include<iomanip>
using namespace std ; 

typedef struct
{
	int f, r;
	int data[100];
} Queue;


Queue queue = {-1, -1}; //main queue for FIFO
int frames[100] ;
int F; //no of frames
int P; //no of pages
int pages[100];
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
		cout<<frames[i] << " " ; 
	}
	cout<<endl; 
}

int findFrame(int page)
{
	// returns index of page in any frame of else -1 if not found(page fault)
	for (int i = 0; i < F; i++)
	{
		if (frames[i]== page)
			return i; //found at frame i
	}
	return -1;
}

int getEmptyFrame()
{
	// get the first empty frame .
	for (int i = 0; i < F; i++)
	{
		if (frames[i]==0)
			return i;
	}
	return -1 ; 
}

void FIFO()
{
	int faults = 0;
	int page = 0;

	for (int p = 0; p < P; p++) //pages[p] is the current page considered . p is the pointer here
	{
		int page = pages[p] ; 
		int frame = findFrame(page) ; 
		if (frame == -1) //not found
		{
			faults++;
			int emptyFrame = getEmptyFrame() ; 
			int selectedFrame  = emptyFrame!=-1 ? emptyFrame : dequeue() ;  //selected frame to put the page. If any empty frame found initally use that else use the FIFO order for frames. 

			frames[selectedFrame] = page ;
			enqueue(selectedFrame);
		}
	}
	cout<<"FIFO : Page Faults = " << faults <<endl; 
}


void LRU()
{
	
}

void LFU()
{

} 

int main(void)
{
	cout << "Enter no of frames : ";
	cin >> F;
	cout << "\nEnter no of pages (page > 0) : ";
	cin >> P;
	cout << "\nEnter page numbers : ";
	for (int i = 0; i < P; i++)
		cin >> pages[i];
	FIFO() ; 
}