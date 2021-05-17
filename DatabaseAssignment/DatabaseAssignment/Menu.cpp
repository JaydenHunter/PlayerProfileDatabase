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
		cout << "\nWhat would you like to do?\n";
		cout << "\t1. View All Records\n";
		cout << "\t2. Add A Record\n";
		cout << "\t3. Find A Record\n";
		cout << "\t4. Exit\n";

		switch (AskNumberRange("Enter an option (1-4): ", 1,4))
		{
		case 1:
			PrintProfiles();
			break;
		case 2:
			break;
		case 3:
			SearchProfile();
			break;
		case 4:
			running = false;
			break;

		}
	}
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
	system("cls");
	if (pData != nullptr)
	{
		ProfileFoundMenu(pData);
	}
	else
	{
		cout << "Player not found!\n";
	}
}

void Menu::EditProfile(PlayerData* pData)
{
	char* askName = AskString("Enter a name: ");
	char name[NAME_LENGTH];
	strcpy_s(name, NAME_LENGTH, askName);

	int newHighscore = AskNumber("Enter a new highscore: ");
	pData->SetName(name);
	pData->SetHighscore(newHighscore);
	DataHandler::Get()->SaveAllProfiles();
}

void Menu::ProfileFoundMenu(PlayerData* pData)
{
	
	printf("Player Found: \n\tName: %s | Highscore: %i\n", pData->GetName(), pData->GetHighscore());
	cout << "\n What would you like to do?";
	cout << "\n1. Edit Player";
	cout << "\n2. Return\n";

	switch (AskNumberRange("Enter an option (1-2): ", 1, 2))
	{
	case 1:
		EditProfile(pData);
		break;
	default:
		system("cls");
		break;

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
	cout << question;
	int number;
	cin >> number;
	return number;
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
