#include <iostream>
#include "PlayerData.h"

//--------------------------------------
// Constructors
//--------------------------------------
PlayerData::PlayerData()
{
	strcpy_s(name, NAME_LENGTH, "default");
	highscore = 0;
}

PlayerData::PlayerData(const char* name, int highscore)
{
	strcpy_s(this->name, NAME_LENGTH, name);
	this->highscore = highscore;
}

//--------------------------------------
// Getters and Setters
//--------------------------------------
const char* PlayerData::GetName()
{
	return name;
}

void PlayerData::SetName(char* name)
{
	strcpy_s(this->name, NAME_LENGTH, name);
}

int PlayerData::GetHighscore()
{
	return highscore;
}

void PlayerData::SetHighscore(int highscore)
{
	this->highscore = highscore;
}
