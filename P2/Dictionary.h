#pragma once
#include "Board.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class Dictionary
{
public:
	Dictionary(string fname, Board b);
	void clueGiver();
	void setMap(Board b);
	void helper(string pos);

private:
	string filename;
	map <string, vector<string>> synonyms;
	map<string, string> wordList;
	void loadInfo();
};