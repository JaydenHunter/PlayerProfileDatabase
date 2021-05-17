#include "Menu.h"
#include <iostream>
#include "DataHandler.h"
#include "PlayerData.h"

using std::cin;
using std::cout;
using std::endl;

//--------------------------------------
// Constructor
//--------------------------------------
Menu::Menu()
{
	running = true;
}

//--------------------------------------
// Main Menu Loop
//--------------------------------------
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
			AddProfile();
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

//--------------------------------------
// Print out all profiles to console
//--------------------------------------
void Menu::PrintProfiles()
{
	system("cls");
	cout << "\n";
	DataHandler::Get()->PrintAll();
	cout << "\n";
}
//--------------------------------------
// Menu for adding a new Profile
//--------------------------------------
void Menu::AddProfile()
{
	char* askName = AskString("Enter a name: ");
	char name[NAME_LENGTH];
	strcpy_s(name, NAME_LENGTH, askName);

	int newHighscore = AskNumber("Enter a new highscore: ");

	PlayerData pData;
	pData.SetName(name);
	pData.SetHighscore(newHighscore);
	DataHandler::Get()->AddProfile(pData);
}

//--------------------------------------
// Menu for searching for a Profile
//--------------------------------------
void Menu::SearchProfile()
{
	char* askName = AskString("Enter a name to search for: ");
	char name[NAME_LENGTH];
	strcpy_s(name, NAME_LENGTH, askName);

	PlayerData* pData = DataHandler::Get()->SearchProfile(name);
	system("cls");

	//Checks if the profile has been found
	if (pData != nullptr)
	{
		ProfileFound(pData);
	}
	else
	{
		cout << "Player not found!\n";
	}
}

//--------------------------------------
// Menu for Editing a Profile
//--------------------------------------
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

//--------------------------------------
// Menu once a profile has been found
//--------------------------------------
void Menu::ProfileFound(PlayerData* pData)
{
	printf("Player Found: \n\tName: %s | Highscore: %i\n", pData->GetName(), pData->GetHighscore());
	cout << "\n What would you like to do?";
	cout << "\n1. Edit Player";
	cout << "\n2. Return\n";

	//Edit and Return options
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

//--------------------------------------
// Asks user for a number between a given range
//--------------------------------------
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

//--------------------------------------
// Asks user for any number without range
//--------------------------------------
int Menu::AskNumber(const char* question)
{
	cout << question;
	int number;
	cin >> number;
	return number;
}

//--------------------------------------
// Asks user for a string (Char Array)
//--------------------------------------
char* Menu::AskString(const char* question)
{
	cout << question;
	char name[NAME_LENGTH];
	cin >> name;
	return name;
}
