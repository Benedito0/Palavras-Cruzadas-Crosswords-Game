#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include "Board.h"
#include "Dictionary.h"

using namespace std;

string upperCase(string word)
{
	for (unsigned int l = 0; l < word.length(); l++)
	{
		word[l] = toupper(word[l]);
	}

	return word;
}

int main()
{
	int mode, rows, columns;
	vector<vector<char>> charList;
	int signal = 0;
	string fname;
	Board b;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	cout << "CrossWords Puzzle Creator" << endl;
	cout << "=========================" << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << "  ...  " << endl;
	cout << "POSITION (LcD / CTRL-Z = STOP)" << endl;
	cout << "LcD stands for Line column Direction" << endl;
	cout << "  ...  " << endl;
	cout << "--------------------------" << endl;
	cout << "Options:" << endl;
	cout << "1- Create puzzle" << endl;
	cout << "2- Resume puzzle" << endl;
	cout << "0- Exit" << endl << endl;
	cout << "Option ?? ";
	cin >> mode;

	switch (mode)
	{
	case 1:
	{
		cout << "Give rows: ";
		cin >> rows;
		cout << "Give columns: ";
		cin >> columns;

		if (rows > 26)
			rows = 26;

		if (columns > 26)
			columns = 26;

		charList = b.boardCreator(rows, columns);
		b.printBoard(charList, rows, columns);

		break;
	}
	case 2:
	{
		charList = b.boardLoader();
		rows = charList.size();
		columns = charList[0].size();
		signal = 1;
		fname = b.getName();
		break;
	}
	default:
	{
		cout << "Invalid option!" << endl;
		exit(0);
		break;
	}
	}

	string position, word;
	bool anotherOp = true;

	if (signal == 0)
	{
		cout << endl << "Give dictionary: ";
		cin >> fname;
	}

	Dictionary d(fname);

	do
	{
		cout << endl << "Position (LcD / press CTRL-Z to end): ? ";
		cin >> position;
		if (cin.eof())
		{
			anotherOp = false;
			char cont;

			cin.clear();
			cout << "Do you wish to finish (F) or pause (P)?: ";
			cin >> cont;

			if (cont == 'f' || cont == 'F')
			{
				b.boardFinisher(charList, rows, columns, d);
			}
			else if (cont == 'p' || cont == 'P')
			{
				b.storeBoard(charList, d);
			}
		}
		else
		{
			cout << "Word (- = remove): ? ";
			cin >> word;
			word = upperCase(word);

			while (!d.wordValidity(word) && word != "-" && word != "?")
			{
				cout << "Word does not belong to the dictionary, try again!" << endl;
				cout << "Word (- = remove): ? ";
				cin >> word;
				word = upperCase(word);
			}

			if (word == "-")
			{
				charList = b.removeWord(charList, position);
			}
			else if (word == "?")
			{
				cout << "Sorry, we haven't implemented that yet..." << endl;
				return 0;
			}
			else charList = b.boardWriter(charList, position, word);
		}
	} while (anotherOp);

	system("pause");
	return 0;
}

