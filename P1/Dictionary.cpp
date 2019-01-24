#include "stdafx.h"
#include "Dictionary.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

void Dictionary::loadInfo()
{
	string line;
	vector<string> lines;

	ifstream infile(filename);

	if (infile.fail())
	{
		cerr << "Error: file not found!" << endl;
		exit(1);
	}

	while (!infile.eof())
	{
		getline(infile, line);
		lines.push_back(line);
	}

	vector<string>::iterator it;
	for (it = lines.begin(); it != lines.end(); it++)
	{
		string token;
		if (it->find('\:') != string::npos)
		{
			string delimeter = ": ";
			size_t pos = it->find(delimeter);
			token = it->substr(0, pos);

			for (unsigned int l = 0; l < token.length(); l++)
			{
				token[l] = toupper(token[l]);
			}

			synonyms[token];
			it->erase(0, pos + delimeter.length());
		}

		while (it->find(',') != string::npos)
		{
			string delimeter = ", ";
			size_t pos = it->find(delimeter);
			string word = it->substr(0, pos);
			synonyms[token].push_back(word);
			it->erase(0, pos + delimeter.length());
		}
		synonyms[token].push_back(*it);
	}
}

Dictionary::Dictionary(string fname)
{
	filename = fname;
	loadInfo();
}

bool Dictionary::wordValidity(string word)
{
	bool isValid = false;
	if (synonyms.find(word) != synonyms.end()) {
		isValid = true;
		return isValid;
	}
	return isValid;
}

string Dictionary::getFile()
{
	return filename;
}

void Dictionary::setName(string name)
{
	filename = name;
}
