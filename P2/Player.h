#pragma once
#include <ctime>
#include <string>

using namespace std;

class Player
{
public:
	Player(string name);
	void setTime();
	void setHelps(int n);

private:
	string pName;
	int gameTime, timeB, timeE, helps;
	void printPlayers();
};

