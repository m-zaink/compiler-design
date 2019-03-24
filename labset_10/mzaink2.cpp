#include <bits/stdc++.h>

using namespace std;

int nt, nnt, np;

char first[255][255], follow[255][255];
char productions[20][20];
char terminals[20], nonterminals[20];

bool isIn(char firsts[], char terminal) {
	for(int i = 0; firsts[i] != '\0'; ++i) 
		if (terminal == firsts[i]) return true;
	return false;
}

bool containsEpsilon(char firsts[]) {
	for(int i = 0; firsts[i] != '\0'; ++i) 
		if ('#' == firsts[i]) return true;
	return false;
}

int findProduction(char nonterminal, char terminal) {
	for(int i = 0; i < np; ++i) {
		if (nonterminal == productions[i][0]) {	
			if(containsEpsilon(first[nonterminal]) && isIn(follow[nonterminal], terminal))
				return i;	
			if (isIn(first[nonterminal], terminal))
				return i;
		}
	}
	return -1;
}

int main() {
	cout << "Enter the numbers of productions : ";
	cin >> np;
	cout << "Enter the number of non-terminals : ";
	cin >> nnt;
	cout << "Enter the number of terminals : ";
	cin >> nt;

	cout << "Enter the productions : " << endl; 
	for(int i = 0; i < np; ++i)
		cin >> productions[i];

	getchar();	
	cout << "Enter the non-terminals : " << endl;
	for(int i = 0; i < nnt; ++i)
		cin >> nonterminals[i];

	getchar();
	cout << "Enter the terminals : " << endl;
	for(int i = 0; i < nt; ++i) 
		cin >> terminals[i];

	terminals[++nt] = '$';

	cout << "Enter the first of following productions : ";
	for(int i = 0; i < np; ++i) {
		cout << productions[i] << endl;
		cin >> first[productions[i][0]];
	}

	cout << "Enter the follow of following symbols : " << endl;
	for(int i = 0; i < nnt; ++i) {
		cout << nonterminals[i] << " : ";
		cin >> follow[nonterminals[i]];
	}

	system("clear");
	cout << "\t";
	for(int i = 0; i < nt; ++i)
		cout << terminals[i] << "\t";

	cout << endl;

	for(int i = 0; i < nnt; ++i) {
		cout << nonterminals[i] << "\t";
		for(int j = 0; j < nt; ++j) {
			int pos = findProduction(nonterminals[i], terminals[j]);
			if (pos == -1)
				cout << "\t";
			else 
				cout << productions[pos] << "\t";
		}
		cout << endl;
	}
	return 0;
}

