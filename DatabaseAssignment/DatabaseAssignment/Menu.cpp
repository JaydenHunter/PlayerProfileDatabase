#include "Menu.h"
#include <iostream>
#include "DataHandler.h"
#include "PlayerData.h"

using std::cin;
using std::cout;
using std::endl;

Menu::Menu()
{
	running = true;
}

Menu::~Menu()
{
}

void Menu::MenuLoop()
{
	while (running)
	{
		//system("cls");
		cout << "\nWhat would you like to do?\n";
		cout << "\t1. View All Records\n";
		cout << "\t2. Add A Record\n";
		cout << "\t3. Modify A Record\n";
		cout << "\t4. Find A Record\n";
		cout << "\t5. Exit\n";

		switch (AskNumberRange("Enter an option (1-5): ", 1, 5))
		{
		case 1:
			PrintProfiles();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			SearchProfile();
			break;
		case 5:
			running = false;
			break;

		}
	}
}

void Menu::PrintOptions()
{
	
}

void Menu::PrintProfiles()
{
	system("cls");
	cout << "\n";
	DataHandler::Get()->PrintAll();
	cout << "\n";
}

void Menu::AddProfile()
{
}

void Menu::SearchProfile()
{
	char* askName = AskString("Enter a name to search for: ");
	char name[NAME_LENGTH];
	strcpy_s(name, NAME_LENGTH, askName);
	PlayerData* pData = DataHandler::Get()->SearchProfile(name);
	if (pData != nullptr)
	{
		cout << "Player Found\n" << pData->GetName();
	}
	else
	{
		cout << "Player not found!\n";
	}
}

int Menu::AskNumberRange(const char* question, int min, int max)
{
	cout << question;

	int number;
	bool valid = false;
	while (!valid)
	{
		cin >> number;
		if (number > max || number < min)
			cout << "\nInvalid input, try again!\n";
		else
			valid = true;
	}
	return number;
}

int Menu::AskNumber(const char* question)
{
	return 0;
}

char* Menu::AskString(const char* question)
{
	cout << question;
	char name[NAME_LENGTH];
	cin >> name;
	cout << endl;
	name[NAME_LENGTH - 1] = '0';
	return name;
}
