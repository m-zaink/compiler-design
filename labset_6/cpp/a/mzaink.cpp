// Author  : mzaink
// Program : FIFO Page replacement Algorithm

#include <bits/stdc++.h>

using namespace std;

void updateBuffer(int frameBuffer[], int frameSize, int pageIn) {
	int temp = frameBuffer[0];
	for(int i = 0; i < frameSize - 1; ++i) 
		frameBuffer[i] = frameBuffer[i+1];
	frameBuffer[frameSize - 1] = pageIn;
}

bool frameContains(int frameBuffer[], int frameSize, int pageIn) {
	for(int i = 0; i < frameSize; ++i)
		if(frameBuffer[i] == pageIn)
			return true;

	return false;
}

int fifo(int pageStack[], int numberOfPages, int frameSize) {
	int pageFault = 0, frameBuffer[frameSize];
	cout << "Pages that required faults : " << endl;
	for(int i = 0; i < numberOfPages; ++i) {
		if(i < frameSize) {	
			pageFault++;
			frameBuffer[i] = pageStack[i];
			cout << pageStack[i] << "\t";
			continue;
		}
		if(frameContains(frameBuffer, frameSize, pageStack[i]))
			continue;
		updateBuffer(frameBuffer, frameSize, pageStack[i]);
		pageFault++;
		cout << pageStack[i] << "\t";
	}

	cout << endl << "Number of page faults : " << pageFault << endl;
}


void readPageStack(int pageStack[], int numberOfPages) {
	cout << "Enter the page list : \n";
	for(int i = 0; i < numberOfPages; ++i) {
		cin >> pageStack[i];
	}
}

int main() {
	int frameSize, numberOfPages;
	cout << "Enter the number of pages : ";
	cin >> numberOfPages;

	int pageStack[numberOfPages];

	readPageStack(pageStack, numberOfPages);

	cout << "Enter the frame size : ";
	cin >> frameSize;

	fifo(pageStack, numberOfPages, frameSize);
}

// Output [2]

/*
	Enter the number of pages : 12
	Enter the page list : 
	1 2 3 3 4 5 5 6 7 8 9 1
	Enter the frame size : 3
	Pages that required faults : 
	1	2	3	4	5	6	7	8	9	1	
	Number of page faults : 10
*/