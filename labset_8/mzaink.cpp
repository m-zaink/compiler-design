#include <bits/stdc++.h>
#include <ctype.h>

using namespace std;

int main(void) {
	string identifier;
	int state = 0;
	bool flag = true;

	cout << "Enter the identifier : ";
	cin >> identifier;

	for(int i = 0; i < identifier.length(); ++i) 
	{
		if(i == 0 && !(identifier[i] == '_'  || isalpha(identifier[i])))
		{
			flag = false;
			break;
		}	
		else if(i != 0 && !isalnum(identifier[i]) && !identifier[i] == '_')
		{	
			flag = false; 
			break;
		}
	}

	if(!flag)
		cout << "INVALID IDENTIFIER";
	else 
		cout << "Congrats. Valid identifier.";

	cout << endl;
}