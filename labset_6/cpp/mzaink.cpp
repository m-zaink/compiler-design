// Author  : mzaink
// Program : FIFO Page replacement Algorithm

#include <bits/stdc++.h>

using namespace std;

void readPageQueue(int pageQueue[], int pages)
{
	//Utility function to read the page reference string.

	cout << "Enter the page reference string : " << endl;

	for (int i = 0; i < pages; ++i)
		cin >> pageQueue[i];

	cout << "Page Reference String read completed." << endl;
}

bool containsPage(int frameString[], int pageNumber, int frames)
{
	//Utility function to check if the page requested is already
	//present in the frameString.
	//Returns 'true' if present. Otherwise false.
	for (int i = 0; i < frames; ++i)
		if (frameString[i] == pageNumber)
			return true;
	return false;
}

void fifoPageReplacement(int pageQueue[], int pages, int frames)
{
	//Function to implement the FIFO page replacement algorithm

	//var :
	//j : to keep track of oldest page so far.
	//counter : to keep track of number of page faults.
	int j = 0, counter = 0;
	int frameString[frames];
	string pageFaults = "";
	cout << "\t\t\t\t\t\t\t";
	for (int i = 0; i < pages; ++i)
	{
		if (!containsPage(frameString, pageQueue[i], frames))
		{
			frameString[j] = pageQueue[i];
			cout << "\t" << pageQueue[i];
			j = (j + 1) % frames;
			++counter;
		}
	}

	cout << endl
		 << "FIFO\t\t\t\t" << counter << endl;
}

int getLeastRecentlyUsed(int pageCount[], int pages, int frameString[], int frames, int timestamp)
{
	//Utility function that returns the least recently used page that is 
	//present in the FrameString.

	//var :
	//pos : to keep track of the position of the page to replace
	//min : to keep track which has the least timestamp => meaning least recently used.	

	int pos = INT_MIN, min = INT_MAX;
	for(int i = 0; i < frames; ++i) 
		if(pageCount[frameString[i] % pages] < min)
			//%pages simply helps in bringing the indices in the 
			//range 0 to pages - 1 for easy indexing and memory efficiency.
			pos = i, min = pageCount[frameString[i] % pages];
	
	pageCount[pos] = timestamp;	//update the timestamp of the page to replaced.
	return pos;
}

void lruPageReplacement(int pageQueue[], int pages, int frames)
{
	//Function to implement the LRU Page Replacement algorithm.

	//var :
	//couter : to keep track of # of page faults.
	//pos : to keep track of which page from pageString to replace next.
	int counter = 0, pos = -1;

	//var:
	//frameString : array to hold the pages in memory.
	//pageCount : an auxiliary array to hold the timestamp of the pages
	//i.e. when they were last used.
	int frameString[frames] = {0}, pageCount[pages];

	for(int i = 0; i < pages; ++i) 
	//initializing the pageCount to defaults.
		pageCount[pages] = INT_MIN;
	
	//ignore this place. Just o/p formatting.
	cout << "\t\t\t\t\t\t\t";

	for (int i = 0; i < pages; ++i)
	{
		if (!containsPage(frameString, pageQueue[i], frames))
		{
			//if page not already present in the frameString.
			if(!(i < frames))
				pos = getLeastRecentlyUsed(pageCount, pages, frameString, frames, i);
			else
				pageCount[i] = i, pos = i;
			frameString[pos] = pageQueue[i];
			cout << "\t" << pageQueue[i];
			++counter;
		}
	}

	cout << endl
		 << "LRU\t\t\t\t" << counter << endl;
}

int main(void)
{
	//var :
	//pages : no of pages to be alloted memory
	//frames : frameSize of the
	int pages, frames;

	cout << "Enter the number of pages : ";
	cin >> pages;
	cout << "Enter the number of frames: ";
	cin >> frames;

	//pageQ : array to represent the Page Reference String
	int pageQueue[pages];

	readPageQueue(pageQueue, pages);

	cout << endl << "Algorithm Name\t\t# of page faults\t\tPages fault for" << endl;

	fifoPageReplacement(pageQueue, pages, frames);
	lruPageReplacement(pageQueue, pages, frames);

	return 0;
}