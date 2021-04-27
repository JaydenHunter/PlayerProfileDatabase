#include <iostream>
#include "PlayerData.h"

PlayerData::PlayerData()
{
	strcpy_s(name, 64, "default");
	highscore = 0;
}

const char* PlayerData::GetName()
{
	return name;
}

void PlayerData::SetName(char* name)
{
	strcpy_s(this->name, 64, name);
}

int PlayerData::GetHighscore()
{
	return highscore;
}

void PlayerData::SetHighscore(int highscore)
{
	this->highscore = highscore;
}



