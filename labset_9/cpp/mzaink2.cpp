#include <bits/stdc++.h>
#include <ctype.h>

using namespace std;

char productions[10][10];
int n;

int getPosition(char curHead) {
	for(int i = 0; i < n; ++i)
		if(curHead == productions[i][0])
			return i;
}
int nextPos;

string first(char curHead, int pos) {
	int i;
	string localFirstSym;	
	for(i = pos; productions[i][0] == curHead; ++i) {
		for(int j = 3; productions[i][j] != '\0'; ++j) {
			if(islower(productions[i][j])) {
				localFirstSym.push_back(productions[i][j]);
				break;
			} else if(productions[i][j] != '$') {
				string temp = first(productions[i][j], getPosition(productions[i][j]));
				for(int k = 0; k < temp.length(); ++i) {
					if(temp[i] != '$')
						localFirstSym.push_back(temp[i]);
					else {
						j++;
					}
				}
				
			} else {
				localFirstSym.push_back(productions[i][j]);
				break;
			}
		}
	}

	cout << "{	";
	for(int i = 0; i < localFirstSym.length(); ++i) {
		cout << localFirstSym[i] << "\t";
	}
	cout << "}";
	nextPos = i;
	cout << endl;
	return localFirstSym;
}

void readGrammar() {
	cout << "Enter the productions in the format : A->a" << endl;
	cout << "Enter $ for epsilon" << endl;
	cout << "Enter all productions with same head consecutively." << endl;
	cout << "** Assuming first productions has start symbol as it's hear" << endl << endl;
	for(int i = 0; i < n; ++i) {
		cout << "Production # " << i << " : ";
		cin >> productions[i];
	}
}

int main() {
	cout << "Enter the # of productions : ";
	cin >> n;
	readGrammar();

	for(int i = 0; i < n; ) {
		cout << "FIRST ( " << productions[i][0] << " ) : " << endl;
		first(productions[i][0], i);
		i = nextPos;
		cout << endl;
	}
	return 0;	
}