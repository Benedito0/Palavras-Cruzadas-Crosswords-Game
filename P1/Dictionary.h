#pragma once
#include <map>
#include <string>
#include <vector>

using namespace std;

class Dictionary
{
public:
	Dictionary(string fname);
	bool wordValidity(string word);
	string getFile();
	void setName(string name);

private:
	string filename;
	map <string, vector<string>> synonyms;
	void loadInfo();
};
