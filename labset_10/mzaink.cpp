#include <bits/stdc++.h>

int np, nnt, nt;
// increment nt once you read it to accommodate $
char first[255][255], follow[255][255];
char nonterminals[10], terminals[10];
char parseTable[255][255];

void init() {
	for(int i = 0; i < 255; ++i)
		(first[i] = '|'), (follow[i] = '|'), (parseTable[i][0] = '|');
}

int main() {
	cout << "Enter the number of productions : ";
	cin >> np;

	cout << "Enter the number of nonterminals : "
	cin >> nnt;

	cout << "Enter the number of terminals : ";
	cin >> nt;

	init();
	cout << "Enter the productions : " << endl;

	for(int i = 0; i < np; ++i)
		cin >> productions[i];

	cout << "Enter the non-terminals : " << endl;

	for(int i = 0; i < nnt; ++i) {
		cin >> nonterminals[i];
		parseTable[nonterminals[i]][0] = nonterminals[i];
	}

	cout << "Enter the terminals : " << endl;
	for(int i = 0; i < nt; ++i) {
		cin >> terminals[i];
		parseTable
	}


	cout << "Enter the first of following symbols : " << endl;

	for(int i = 0; i < nnt; ++i) {
		cout << "Symbol ( " << nonterminals[i] << " ) : ";
		cin >> first[nonterminals[i]];
	}

	for(int i = 0; i < nt; ++i) 
		first[terminals[i]] = terminals[i];

	cout << "Enter the follow of following symbols : " << endl;

	for(int i = 0; i < nnt; ++i) 
		cin >> follow[nonterminals[i]];


	return 0;
}
