#pragma once
class PlayerData;

class Menu
{
public:
	Menu();
	~Menu();

	void MenuLoop();

private:

	void PrintProfiles();
	void AddProfile();
	void SearchProfile();
	void EditProfile(PlayerData* pData);
	void ProfileFoundMenu(PlayerData* pData);
	int AskNumber(const char* question);
	int AskNumberRange(const char* question, int min, int max);
	char* AskString(const char* question);

private:
	bool running;
};

