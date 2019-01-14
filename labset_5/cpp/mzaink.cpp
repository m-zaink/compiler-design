#include <bits/stdc++.h>

using namespace std;

//array to hold the size of each process
int process[100];
//array to hold the size of each hole
int hole[100];

//var 
//processCount : # of processes
//holeCount : # of holes
int processCount, holeCount;

void readHolesAndProcesses() {
	//Utility function to read the sizes of each hole and each process.

	cout << endl << "Enter the size of each hole : \n";

	//Read for each hole
	for(int i = 0; i < holeCount; ++i) {
		cout << "Hole [ " << i  << " ] : ";
		cin >> hole[i];
	}

	cout << endl << "Enter the size of each process : \n";

	//Read for each process
	for(int i = 0; i < processCount; ++i) {
		cout << "Process [ " << i << " ] : ";
		cin >> process[i];
	}
}

void copyVector(int temp[]) {
	//Utility function to copy the hole vector into the parameter vector.
	for(int i = 0; i < holeCount; ++i)
		temp[i] = hole[i];
}

int findSmallest(int bestFitHoles[], int size) {
	//Utility funtion to find the smallest hole that satifies the size constraint

	int min = INT_MAX, pos;
	for(int i = 0; i < processCount; ++i) {
		if(bestFitHoles[i] >= size && bestFitHoles[i] <= min)
			min = bestFitHoles[i], pos = i;
	}

	if(min == INT_MAX)
		return -1;
	return pos;
}

void bestFit() {
	//Function to implement best-fit logic.
	//It finds the smallest hole that satifies the process requirement.
	
	int bestFitHoles[holeCount], pos;
	copyVector(bestFitHoles);


	cout << endl << "Best Fit : " << endl;
	cout << endl << "Process\t\tHole" << endl;

	for(int i = 0; i < processCount; ++i) {
		pos = findSmallest(bestFitHoles, process[i]);
		if(pos != -1)
			bestFitHoles[pos] -= process[i];
		cout << i << "\t\t" << pos << endl;
	}

	cout << endl;
}

int findLargest(int worstFitHoles[], int size) {
	int max = 0, pos;
	for(int i = 0; i < processCount; ++i) {
		if(worstFitHoles[i] >= size && max < worstFitHoles[i])
			max = worstFitHoles[i], pos = i;
	}
	if(max == 0) 
		return -1;
	return pos;
}

void worstFit() {
	int worstFitHoles[holeCount], pos;
	copyVector(worstFitHoles);

	cout << endl << "Worst Fit : " << endl;
	cout << endl << "Process\t\tHole" << endl;
	for(int i = 0; i < processCount; ++i) {
		pos = findLargest(worstFitHoles, process[i]);
		if(pos != -1)
			worstFitHoles[pos] -= process[i];
		cout << i << "\t\t" << pos << endl;
	}
	cout << endl;
}

int findFirstFit(int firstFitHoles[],int size) {
	for(int i = 0; i < holeCount; ++i) {
		if(size <= firstFitHoles[i])
			return i;
	}
	return -1;
}

void firstFit() {
	int firstFitHoles[holeCount], pos;
	copyVector(firstFitHoles);

	cout << "First First : " << endl;

	cout << "Process\t\tHole" << endl;
	for(int i = 0; i < processCount; ++i) {
		pos = findFirstFit(firstFitHoles, process[i]);
		if(pos != -1)
			firstFitHoles[pos] -= process[i];
		cout << i << "\t\t" << pos << endl;	
	}
}

int main() {
	cout << "Enter the number of holes : ";
	cin >> holeCount;
	cout << "Enter the number of processes : ";
	cin >> processCount;
	readHolesAndProcesses();

	bestFit();
	worstFit();
	firstFit();

	cout << endl << "** -1 = not allocated" << endl;
	return 0;
}


//Sample Output
/* 
	Enter the size of each hole : 
	Hole [ 0 ] : 10
	Hole [ 1 ] : 20
	Hole [ 2 ] : 50
	Hole [ 3 ] : 5
	Hole [ 4 ] : 100

	Enter the size of each process : 
	Process [ 0 ] : 70
	Process [ 1 ] : 5
	Process [ 2 ] : 10
	Process [ 3 ] : 3
	Process [ 4 ] : 6

	Best Fit : 

	Process		Hole
	0		4
	1		3
	2		0
	3		1
	4		1


	Worst Fit : 

	Process		Hole
	0		4
	1		2
	2		2
	3		2
	4		2

	First First : 
	Process		Hole
	0		4
	1		0
	2		1
	3		0
	4		1
	** -1 = not allocated

*/