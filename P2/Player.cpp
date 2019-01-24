#include "stdafx.h"
#include "Player.h"
#include <fstream>

using namespace std;

Player::Player(string name)
{
	pName = name;
	timeB = time(NULL);
}

void Player::printPlayers()
{
	ofstream outFile("b001_p.txt");

	outFile << pName << " took " << gameTime << " seconds to complete the board and asked for: " << helps
		<< " additional clue(s).";
}

void Player::setTime()
{
	timeE = time(NULL);

	gameTime = timeE - timeB;
	printPlayers();
}

void Player::setHelps(int n)
{
	helps = n;
}
