#pragma once
class PlayerData
{
public:
	PlayerData();
	const char* GetName() ;
	void SetName(char* name);

	int GetHighscore();
	void SetHighscore(int highscore);

private:
	char name[64];
	int highscore;
};

