#include <bits/stdc++.h>

using namespace std;

char productions[10][10];
int n;

void readProductions() {
	for(int i = 0; i < n; ++i) {
		// cout << "Enter the production " << i + 1 << " (use # for epsilon)." << endl;
		cin >> productions[i];
	}
}
int k = 0;
int temp;
char str[10];

void recursiveDescentParsing(char symbol) {
	bool found = false;
	int i;

	for(i = 0; i < n; ++i) {
		temp = k;
		if(productions[i][0] == symbol) {
			for(int j = 3; productions[i][j] != '\0'; ++j) {
				if(str[k] == '#')
					k++;
				else if(isupper(productions[i][j])) {
					found = true;
					recursiveDescentParsing(productions[i][j]);
				} else if(productions[i][j] == str[k]) {
					found = true;
					++k;
				} else if(productions[i][j] == '#') {
					found = true;
					return;
				} else {
					k = temp;
					break;
				}
			}
		}
	}

	if( ( i >= n) && !found && k = strlen(str)) {
		cout << "Invalid input !!!";
		cout << endl << endl;
	} 
}

int main() {
	cout << "Enter the number of productions : ";
	cin >> n;

	readProductions();

	while(true) {
		k = 0;
		cout << "Enter the input string : ";
		cin >> str;

		recursiveDescentParsing(productions[0][0]);

		if(k == strlen(str)) {
			cout << "String accepted !!! ";
		} else {
			cout << "Invalid String !! ";
		}

		cout << endl << endl;
		getchar();
		getchar();
		system("clear");
	}

	return 0;
}