#pragma once
#define NAME_LENGTH 64
class PlayerData
{
public:
	//Constructors
	PlayerData();
	PlayerData(const char* name, int highscore = 0);

	//Getters and Setters
	const char* GetName();
	void SetName(char* name);
	
	int GetHighscore();
	void SetHighscore(int highscore);

private:
	char name[NAME_LENGTH];
	int highscore;
};

