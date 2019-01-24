#pragma once
#include <vector>
#include <map>
#include <string>
#include "Dictionary.h"

using namespace std;

namespace
{
	map<string, bool> isShared;
}

class Board
{
public:
	void printBoard(vector<vector<char>> sudoBoard, int row, int column);
	vector<vector<char>> boardCreator(int row, int column);
	void setName(string name);
	vector<vector<char>> boardLoader();
	bool wordTester(vector<vector<char>> sudoBoard, string pos, string word);
	vector<vector<char>> boardWriter(vector<vector<char>> sudoBoard, string pos, string word);
	vector<vector<char>> removeWord(vector<vector<char>> sudoBoard, string pos);
	void storeBoard(vector<vector<char>> sudoBoard, Dictionary d);
	void boardFinisher(vector<vector<char>> sudoBoard, int row, int column, Dictionary d);
	string getName();

private:
	int rows;
	int columns;
	vector<vector<char>> sudoBoard;
	map<string, string> wordList; // <position,word>
	map<string, bool> sharedCoordenates; // estrutra de dados que vai identificar quais as coordenadas usadas peor duas palavras
	map<string, bool> getSharedCoordenates();
	void setSharedCoordenates(string coordinates, bool isCoordinate);
	void setSharedCoordenateValue(string coordinate, bool value);
	bool isCoordinateShared(string coordinate);
	string fname;
};
