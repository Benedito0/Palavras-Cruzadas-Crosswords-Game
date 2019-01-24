#pragma once
#include <vector>
#include <map>
#include <string>

using namespace std;

namespace
{
	map<string, bool> isShared;
}

class Board
{
public:
	Board();
	void setName(string name);
	string getName();
	map<string, string>getMap();
	bool boadFull();
	bool wordTester(string position, string word);
	bool boardValidator();
	void boardWriter(string pos, string word);
	void removeWord(string pos);

private:
	int columns;
	int rows;
	string fname;
	vector<vector<char>> sudoBoard;
	map<string, string> wordList, verifier;
	void boardCypher();
	void printBoard();
	map<string, bool> sharedCoordenates; // estrutra de dados que vai identificar quais as coordenadas usadas peor duas palavras
	map<string, bool> getSharedCoordenates();
	void setSharedCoordenates(string coordinates, bool isCoordinate);
	void setSharedCoordenateValue(string coordinate, bool value);
	bool isCoordinateShared(string coordinate);
};
