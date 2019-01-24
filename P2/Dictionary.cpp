#include "stdafx.h"
#include "Dictionary.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void Dictionary::setMap(Board b)
{
	wordList = b.getMap();
}

Dictionary::Dictionary(string fname, Board b)
{
	filename = fname;
	loadInfo();

	setMap(b);
}

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

void Dictionary::clueGiver()
{
	map<string, vector<string>> horizontals, verticals;
	srand(time(0));

	for (auto mit = wordList.begin(); mit != wordList.end(); mit++)
	{
		if (mit->first[2] == 'H')
		{
			string key = mit->first.substr(0, 2);
			horizontals[key];
			horizontals[key] = synonyms[mit->second];
		}

		if (mit->first[2] == 'V')
		{
			string key = mit->first.substr(0, 2);
			verticals[key];
			verticals[key] = synonyms[mit->second];
		}
	}

	cout << "Horizontal:" << endl;
	for (auto mit = horizontals.begin(); mit != horizontals.end(); mit++)
	{
		int randomIndex = rand() % mit->second.size();

		cout << mit->first << "        " << mit->second[randomIndex] << endl;

		if (mit->second.size() > 1)
			mit->second[randomIndex].erase();
	}

	cout << endl;

	cout << "Vertical:" << endl;
	for (auto mit = verticals.begin(); mit != verticals.end(); mit++)
	{
		int randomIndex = rand() % mit->second.size();

		cout << mit->first << "        " << mit->second[randomIndex] << endl;

		if (mit->second.size() > 1)
			mit->second[randomIndex].erase();
	}
}

void Dictionary::helper(string pos)
{
	int randomIndex = rand() % synonyms[wordList[pos]].size();

	cout << pos.substr(0, 2) << "        " << synonyms[wordList[pos]][randomIndex];

	if (synonyms[wordList[pos]].size() > 1)
		synonyms[wordList[pos]][randomIndex].erase();
}
