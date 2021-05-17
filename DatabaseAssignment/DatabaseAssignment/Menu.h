#pragma once
class PlayerData;

class Menu
{
public:
	Menu();

	void MenuLoop();

private:

	//Menu Options
	void PrintProfiles();
	void AddProfile();
	void SearchProfile();
	void EditProfile(PlayerData* pData);
	void ProfileFound(PlayerData* pData);

	//Input Requests
	int AskNumber(const char* question);
	int AskNumberRange(const char* question, int min, int max);
	char* AskString(const char* question);

private:
	bool running;
};

