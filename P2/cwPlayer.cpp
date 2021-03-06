#include "stdafx.h"
#include "Board.h"
#include "Dictionary.h"
#include "Player.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <windows.h>

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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	string playerName;

	cout << "Welcome to Crosswords Player!" << endl
		<< "-----------------------------" << endl << endl;
	cout << "The rules are simple, fill the board with the words by indicating" << endl
		<< " the position (LcD - Line column Direction) and the word you wish to place." << endl << endl;
	cout << "To help you, you will be given a synonym of the word you are meant to place" << endl
		<< " in each position." << endl << endl;

	cout << "Enter your player name: ";
	cin >> playerName;
	Player p(playerName);
	cout << endl << endl;

	Board b;
	string filename = b.getName();
	Dictionary d(filename, b);
	string position, word;
	int helps = 0;

	cout << endl << endl << "Clues:" << endl << endl;
	d.clueGiver();

	do {
		cout << endl << "Position ? (LcD): ";
		cin >> position;

		cout << endl << "Word ? (- to remove / ? for another clue): ";
		cin >> word;

		word = upperCase(word);

		if (word == "-")
		{
			b.removeWord(position);
		}
		else if (word == "?")
		{
			helps++;
			d.helper(position);
		}
		else
		{
			if (b.wordTester(position, word))
				b.boardWriter(position, word);
		}

	} while (!b.boadFull());

	if (b.boadFull())
	{
		if (b.boardValidator())
		{
			p.setHelps(helps);
			p.setTime();
			cout << endl;
		}
		else
		{
			cout << endl << "Board incorrectly filled!." << endl;
		}
	}

	system("pause");
	return 0;
}
