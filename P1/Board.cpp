#include "stdafx.h"
#include "Board.h"
#include "Dictionary.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <windows.h>

using namespace std;

void Board::printBoard(vector<vector<char>> sudoBoard, int row, int column)
{
	char lineV = 97, lineH = 65;

	for (int i = -1; i < row; i++)
	{
		if (i == -1)
		{
			cout << setw(3);

			int y = column;
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
			for (int j = 0; j < column; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
				cout << sudoBoard[i][j] << " ";
			}
			lineH++;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

vector<vector<char>> Board::boardCreator(int row, int column)
{
	vector<vector<char>> sudoBoard(row, vector<char>(column));

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++)
		{
			sudoBoard[i][j] = '.'; //'i' refers to the row; 'j' refers to the column
		}
	}

	return sudoBoard;
}

void Board::setName(string name)
{
	fname = name;
}

string Board::getName()
{
	return fname;
}

vector<vector<char>> Board::boardLoader()
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
	vector<vector<char>> sudoBoard(height);

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

	row = sudoBoard.size();
	columns = sudoBoard[0].size();

	printBoard(sudoBoard, row, columns);

	return sudoBoard;
}

bool Board::wordTester(vector<vector<char>> sudoBoard, string pos, string word)
{
	int rowNum = pos[0] - (int) 'A';
	int columnNum = pos[1] - (int) 'a';
	int wSize = word.length();
	string coordinate;

	char direction = pos[2];
	int isH = (direction == 'H') ? 1 : 0;
	int isV = (direction == 'V') ? 1 : 0;

	int maxX = rowNum + (wSize * isV);
	int maxY = columnNum + (wSize * isH);

	if (maxX < 0 || maxX > sudoBoard.size()) //cabe na board na vertical?
	{
		cout << "Error: word does not fit provided board!" << endl;
		return false;
	}

	if (maxY < 0 || maxY > sudoBoard[0].size()) //cabe na board na horizontal?
	{
		cout << "Error: word does not fit provided board!" << endl;
		return false;
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

	for (map<string, string>::const_iterator mit = wordList.begin(); mit != wordList.end(); mit++)
		if (word == mit->second)
		{
			cout << "Word has already been inputed!" << endl;
			return false;
		}


	wordList[pos] = word;

	return true;
}

vector<vector<char>> Board::boardWriter(vector<vector<char>> sudoBoard, string pos, string word)
{
	int rowNum = pos[0] - (int) 'A';
	int columnNum = pos[1] - (int) 'a';
	int wSize = word.length();

	char direction = pos[2];
	int isH = (direction == 'H') ? 1 : 0;
	int isV = (direction == 'V') ? 1 : 0;

	if (wordTester(sudoBoard, pos, word) == false)
	{
		cerr << "Try again!" << endl;
		return sudoBoard;
	}

	for (int i = 0; i < wSize; i++)
	{
		sudoBoard[rowNum + i * isV][columnNum + i * isH] = word[i];
	}

	if (isV && rowNum - 1 >= 0)
		sudoBoard[rowNum - 1][columnNum] = '#';

	if (isV && rowNum + wSize < sudoBoard.size())
		sudoBoard[rowNum + wSize][columnNum] = '#';

	if (isH && columnNum - 1 >= 0)
		sudoBoard[rowNum][columnNum - 1] = '#';

	if (isH && columnNum + wSize < sudoBoard[0].size())
		sudoBoard[rowNum][columnNum + wSize] = '#';

	int row = sudoBoard.size();
	int column = sudoBoard[0].size();
	printBoard(sudoBoard, row, column);

	return sudoBoard;
}

vector<vector<char>> Board::removeWord(vector<vector<char>> sudoBoard, string pos)
{
	int rowNum = pos[0] - (int) 'A';
	int columnNum = pos[1] - (int) 'a';

	char direction = pos[2];
	int isH = (direction == 'H') ? 1 : 0;
	int isV = (direction == 'V') ? 1 : 0;

	int wSize = wordList[pos].length();

	//apagar caracteres
	for (int i = 0; i < wSize; i++)
	{
		string coordinate = to_string(rowNum + i * isV);
		coordinate.append(to_string(columnNum + i * isH));

		if (sudoBoard[rowNum + i * isV][columnNum + i * isH] != '.' && !this->isCoordinateShared(coordinate))
			sudoBoard[rowNum + i * isV][columnNum + i * isH] = '.';
	}

	//apaga cardinais
	if (isV && rowNum - 1 >= 0)
		sudoBoard[rowNum - 1][columnNum] = '.';

	if (isV && rowNum + wSize < sudoBoard.size())
		sudoBoard[rowNum + wSize][columnNum] = '.';

	if (isH && columnNum - 1 >= 0)
		sudoBoard[rowNum][columnNum - 1] = '.';

	if (isH && columnNum + wSize < sudoBoard[0].size())
		sudoBoard[rowNum][columnNum + wSize] = '.';

	int row = sudoBoard.size();
	int column = sudoBoard[0].size();

	map<string, string>::iterator it;
	it = wordList.find(pos);
	wordList.erase(it);

	printBoard(sudoBoard, row, column);
	return sudoBoard;
}

void Board::storeBoard(vector<vector<char>> sudoBoard, Dictionary d)
{
	ofstream outFile("b001.txt");

	//nome do ficheiro
	outFile << d.getFile() << endl << endl;

	int row = sudoBoard.size();
	int column = sudoBoard[0].size();

	int rowNum = 0;
	int columnNum = 0;

	for (int i = 0; i < row; i++)
	{
		for (int c = 0; c < column; c++)
		{
			outFile << sudoBoard[i][c] << " ";
		}
		outFile << endl;
	}

	outFile << endl;
	map<string, string>::iterator mit;
	for (mit = wordList.begin(); mit != wordList.end(); mit++)
	{
		outFile << mit->first << " " << mit->second << endl;
	}
}

void Board::boardFinisher(vector<vector<char>> sudoBoard, int row, int column, Dictionary d)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++)
		{
			if (sudoBoard[i][j] == '.')
				sudoBoard[i][j] = '#';
		}
	}

	storeBoard(sudoBoard, d);
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
