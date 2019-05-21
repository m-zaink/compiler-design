#include <iostream>
#include <ctype.h>
#include <cstring>

#define MAX_SIZE 20

using namespace std;

typedef struct
{
	char symbol;
	int start, end;
} Nonterminal;

Nonterminal nonTerminals[MAX_SIZE];
int input_string_ptr, number_of_productions, number_of_nonterminals;
char productions[MAX_SIZE][MAX_SIZE];
char input_string[MAX_SIZE];

int getSymbolPos(char symbol)
{
	for (int pos = 0; pos < number_of_nonterminals; ++pos)
		if (nonTerminals[pos].symbol == symbol)
			return pos;
}

void expandNonterminal(char symbol)
{
	const int POS = getSymbolPos(symbol);
	cout << POS << endl;
	for (int i = nonTerminals[POS].start; i < nonTerminals[POS].end;)
	{
		int cur = input_string_ptr;
		char cur_sym;

		for (int j = 3; j < strlen(productions[i]); ++j)
		{
			cur_sym = productions[i][j];
			cout << cur_sym << endl;
			if (isupper(cur_sym))
				expandNonterminal(cur_sym);
			else if (cur_sym == input_string[input_string_ptr])
			{
				if (input_string[input_string_ptr + 1] == '\0')
				{
					cout << "The given string is accepted!" << endl;
					exit(0);
				}
				++input_string_ptr;
			}
			else
			{
				++i;
				input_string_ptr = cur;
				break;
			}
		}
	}
}

void nonTerminalsInit()
{
	int k = 0;
	char sym;
	int start, end;

	nonTerminals[k].symbol = productions[0][0];
	nonTerminals[k].start = 0;

	for (int i = 0; i < number_of_productions; ++i)
	{
		if (productions[i][0] != productions[i + 1][0])
		{
			nonTerminals[k].end = i + 1;
			nonTerminals[k].symbol = productions[i][0];

			if (k == number_of_nonterminals)
				break;

			++k;

			nonTerminals[k].symbol = productions[i + 1][0];
			nonTerminals[k].start = i + 1;
		}
	}
	k--;
}

void readProductions()
{
	system("clear");
	cout << "Enter the productions one after the other." << endl;
	cout << "PS : " << endl;
	cout << "\tEnter productions of same symbol one after the other." << endl;
	cout << "\tUse $ to indicate epsilon." << endl;
	cout << "\tUse the format : A->abc" << endl;
	cout << "\tEnter the productions containing start symbol first." << endl;
	for (int i = 0; i < number_of_productions; ++i)
	{
		cout << "Enter production [ " << i + 1 << " ] : " << endl;
		cin >> productions[i];
		cout << endl;
	}

	nonTerminalsInit();

	cout << "Enter the string to validate : ";
	cin >> input_string;
}

int main()
{
	cout << "Enter the number of productions : ";
	cin >> number_of_productions;

	cout << "Enter the number of non-terminals : ";
	cin >> number_of_nonterminals;

	readProductions();
	expandNonterminal(productions[0][0]);
	cout << "The given string couldn\'t be accepted." << endl;
	exit(1);

	return 0;
}