// Author : mzaink
//

#include <bits/stdc++.h>
#include <ctype.h>

using namespace std;

char productions[10][10];
int n;

void readGrammar() {

	cout << "Enter in the format : A->a" << endl;
	cout << "Use %% for epsilon." << endl;

	for(int i = 0; i < n; ++i) {
		cout << "Production #" << i << " : ";
		cin >> productions[i];
		cout << endl;
	}
}

int getPosition(char curHead) {
	for(int i = 0; i < n; ++i)
		if(productions[i][0] == curHead)
			return i;
}

int first(char curHead, int pos) {

	if(islower(curHead))
	int i;
	cout << "{ ";
	for(i = pos; productions[i][0] == curHead; ++i) {
		if(islower(productions[i][3])) 
			cout << productions[i][3] << "\t";
		else if(productions[i][3] == '%')  {
			if(productions[i][4] == '\0')
				cout << productions[i][3] << "\t";
			else if(productions[getPosition(productions[i][4])][3] == '%')
				cout << productions[i][]
				first(productions[i][4], getPosition(productions[i][4]));
			else
				cout << productions[i][4] << "\t";
		}
		else
			first(productions[i][3], getPosition(productions[i][3]));
	}

	cout << "}";

	return i;
}

int first(char curHead, int pos) {
	for(int i = pos; productions[i][0] == curHead; ++i) {
		if()
	}
}

char firstSym(char curHead) {
	if(islower(curHead)) {
		cout << curHead;
		return '~';
	}
	else if(curHead == '%')
		return '%';
	else
		return '_';
}







int main() {

	cout << "Enter the number of productions : ";
	cin >> n;

	readGrammar();

	for(int i = 0; i < n;) {
		cout << "FIRST ( " << productions[i][0] << " ) " << endl;
		cout << endl;
		i = first(productions[i][0], i);
		cout << endl;
	}
	return 0;
}