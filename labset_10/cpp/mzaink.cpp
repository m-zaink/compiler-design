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
			if(containsEpsilon(first[i]) && isIn(follow[nonterminal], terminal))
				return i;	
			if (isIn(first[i], terminal))
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

	cout << "Enter the first of following productions : " << endl;
	for(int i = 0; i < np; ++i) {
		cout << productions[i] << " : ";
		cin >> first[i];
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

/* OUTPUT : 
Enter the numbers of productions : 3
Enter the number of non-terminals : 2
Enter the number of terminals : 2
Enter the productions : 
S--0A
A--S1
A--1
Enter the non-terminals : 
S
A
Enter the terminals : 
0
1
Enter the first of following productions : 
S--0A : 0
A--S1 : 0
A--1 : 1
Enter the follow of following symbols : 
S : $1
A : $

	0		1		
S	S--0A			
A	A--S1	A--1	
*/

/*
Enter the numbers of productions : 8
Enter the number of non-terminals : 5
Enter the number of terminals : 5
Enter the productions : 
E--TA
A--+TA
A--#
T--FB
B--*FB
B--#
F--(E)
F--i
Enter the non-terminals : 
E
A
T
B
F
Enter the terminals : 
i
+
*
(
)
Enter the first of following productions : 
E--TA : (i
A--+TA : +
A--# : #$)
T--FB : (i
B--*FB : *
B--# : #+$)
F--(E) : (
F--i : i
Enter the follow of following symbols : 
E : $)
A : $)
T : +$)
B : +$)
F : *+$)

	i	+	*	(	)		
E	E--TA			E--TA			
A		A--+TA			A--#		
T	T--FB			T--FB			
B		B--#	B--*FB		B--#		
F	F--i			F--(E)		
*/