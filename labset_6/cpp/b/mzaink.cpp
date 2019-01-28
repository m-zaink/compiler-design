#include <bits/stdc++.h>

using namespace std;
typedef struct {
	int pageNumber;
	int pageFrequency;	
}page;

int leastRecentlyUsed(page pageStack[], int curIndex) {
	int minFreq = INT_MAX, minPage = -1;
	for(int i = curIndex; i >= 0; --i) {
		if(pageStack[i].pageFrequency < minFreq)	
			minPage = i;
	}

	return minPage;
}

bool frameContains(int frameBuffer[], int frameSize, int pageIn) {
	for(int i = 0; i < frameSize; ++i)
		if(frameBuffer[i] == pageIn)
			return true;

	return false;
}

void updateBuffer(int frameBuffer[], int frameSize, int removePage) {

}

void lru(page pageStack[], int numberOfPages, int frameSize) {
	int pageFault = 0, frameBuffer[frameSize];
	cout << "Pages that required faults : " << endl;

	for(int i = 0; i < numberOfPages; ++i) {
		if(i < frameSize) {	
			pageFault++;
			frameBuffer[i] = pageStack[i].pageNumber;
			cout << pageStack[i].pageNumber << "\t";
			continue;
		}

		int pos = leastRecentlyUsed(pageStack, i);
		// }
		if(frameContains(frameBuffer, frameSize, pageStack[i].pageNumbera))
			continue;

		updateBuffer(frameBuffer, frameSize, pos);
		pageFault++;
		cout << pageStack[i] << "\t";
	}

	cout << endl << "Number of page faults : " << pageFault << endl;
}
int main() {

}