#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <Windows.h>

using namespace std;

void Board::printBoard()
{
	char lineV = 97, lineH = 65;

	for (int i = -1; i < rows; i++)
	{
		if (i == -1)
		{
			cout << setw(3);

			int y = columns;
			while (y > 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << lineV << " ";
				lineV++;
				y--;
			}
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << endl << lineH << setw(2);
			for (int j = 0; j < columns; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
				cout << sudoBoard[i][j] << " ";
			}
			lineH++;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Board::setName(string name)
{
	fname = name;
}

string Board::getName()
{
	return fname;
}

Board::Board()
{
	ifstream infile("b001.txt");
	string line;
	vector <string> lines;

	while (!infile.eof())
	{
		getline(infile, line);
		lines.push_back(line);
	}

	//load do dicionário
	int s = 0;					//sinaliza linha empty 
	string file;
	while (!lines[s].empty())
	{
		file = lines[s];
		s++;
	}

	setName(file);

	//load da Board
	int c = s + 1;
	while (c < lines.size() && !lines[c].empty())
	{
		c++;
	}

	int height = c - (s + 1);					//altura da board para o ciclo for
												//vector<vector<char>> sudoBoard(height);
	sudoBoard.resize(height);

	int row = 0;
	for (int i = 2; i < height + 2; i++)
	{
		char token;
		while (lines[i].find(' ') != string::npos)
		{
			string delimeter = " ";
			size_t pos = lines[i].find(delimeter);
			token = lines[i].at(pos - 1);
			sudoBoard[row].push_back(token);
			lines[i].erase(0, pos + delimeter.length());
		}
		row++;
	}

	//load do map
	int t = c + 1;
	lines.erase(lines.begin(), lines.begin() + t);

	vector<string>::iterator it;
	for (it = lines.begin(); it < lines.end(); it++)
	{
		string key, token;
		if (it->find(' ') != string::npos)
		{
			string delimiter = " ";
			size_t pos = it->find(delimiter);
			key = it->substr(0, pos);
			wordList[key];
			it->erase(0, pos + delimiter.length());
			token = *it;
			wordList[key] = token;
		}
	}

	rows = sudoBoard.size();
	columns = sudoBoard[0].size();

	boardCypher();
}

void Board::boardCypher()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			if (sudoBoard[i][j] > 64 && sudoBoard[i][j] < 91)
				sudoBoard[i][j] = '.';
		}
	}

	printBoard();
}

map<string, string> Board::getMap()
{
	return wordList;
}

bool Board::boadFull()
{
	bool isFull = true;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			if (sudoBoard[i][j] == '.')
				return false;
		}
	}
}

bool Board::wordTester(string position, string word)
{
	int rowNum = position[0] - (int) 'A';
	int columnNum = position[1] - (int) 'a';
	int wSize = word.length();
	string coordinate;

	char direction = position[2];
	int isH = (direction == 'H') ? 1 : 0;
	int isV = (direction == 'V') ? 1 : 0;

	bool validPos = false;
	for (auto mit = wordList.begin(); mit != wordList.end(); mit++)
	{
		if (position == mit->first)
			validPos = true;
	}

	if (!validPos)
	{
		cout << "Invalid initial position. Choose from the positions referenced in the clues!" << endl;
		return false;
	}

	if (word.length() != wordList[position].length())
	{
		cout << "Word does not fit the selected position! Try again!" << endl;
	}

	for (int i = 0; i < wSize; i++)
		if (sudoBoard[rowNum + i * isV][columnNum + i * isH] != '.' && sudoBoard[rowNum + i * isV][columnNum + i * isH] != word[i])
		{
			cout << "Error: word does not match previously inputed words!" << endl;
			return false;
		}
		else if (sudoBoard[rowNum + i * isV][columnNum + i * isH] == word[i])
		{
			string coordinate = to_string(rowNum + i * isV);
			coordinate.append(to_string(columnNum + i * isH));
			bool isSharedCo = true;

			isShared.insert(pair<string, bool>(coordinate, isSharedCo));
		}

	verifier[position] = word;
}

void Board::boardWriter(string pos, string word)
{
	int rowNum = pos[0] - (int) 'A';
	int columnNum = pos[1] - (int) 'a';
	int wSize = word.length();

	char direction = pos[2];
	int isH = (direction == 'H') ? 1 : 0;
	int isV = (direction == 'V') ? 1 : 0;

	for (int i = 0; i < wSize; i++)
	{
		sudoBoard[rowNum + i * isV][columnNum + i * isH] = word[i];
	}

	printBoard();
}

void Board::removeWord(string pos)
{
	int rowNum = pos[0] - (int) 'A';
	int columnNum = pos[1] - (int) 'a';

	char direction = pos[2];
	int isH = (direction == 'H') ? 1 : 0;
	int isV = (direction == 'V') ? 1 : 0;

	int wSize = verifier[pos].length();

	//apagar caracteres
	for (int i = 0; i < wSize; i++)
	{
		string coordinate = to_string(rowNum + i * isV);
		coordinate.append(to_string(columnNum + i * isH));

		if (sudoBoard[rowNum + i * isV][columnNum + i * isH] != '.' && !this->isCoordinateShared(coordinate))
			sudoBoard[rowNum + i * isV][columnNum + i * isH] = '.';
	}

	map<string, string>::iterator it;
	it = verifier.find(pos);
	verifier.erase(it);

	printBoard();
}

bool Board::boardValidator()
{
	for (auto mit = wordList.begin(); mit != wordList.end(); mit++)
	{
		if (verifier[mit->first] != mit->second)
			return false;
	}

	return true;
}

map<string, bool> Board::getSharedCoordenates()
{
	return this->sharedCoordenates;
}

void Board::setSharedCoordenates(string coordinates, bool isCoordinate)
{
	this->getSharedCoordenates().insert(pair<string, bool>(coordinates, isCoordinate));
}

void Board::setSharedCoordenateValue(string coordinate, bool value)
{//altera o valor-value da key-coordinate
	map<string, bool> m;

	map<string, bool>::iterator it = m.find(coordinate);
	if (it != m.end())
		it->second = value;
}

bool Board::isCoordinateShared(string coordinate)
{
	map<string, bool>::iterator it = isShared.find(coordinate);
	if (it != isShared.end())
		return it->second;
	else
		return false;
}