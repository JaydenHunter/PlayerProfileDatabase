#pragma once
class Menu
{
public:
	Menu();
	~Menu();

	void MenuLoop();

private:

	void PrintOptions();
	void PrintProfiles();
	void AddProfile();
	void SearchProfile();
	int AskNumber(const char* question);
	int AskNumberRange(const char* question, int min, int max);
	char* AskString(const char* question);

private:
	bool running;
};

