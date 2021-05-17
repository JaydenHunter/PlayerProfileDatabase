#include <iostream>
#include <crtdbg.h>
#include "DataManager.h"
#include "PlayerData.h"

using std::cin;
using std::cout;
using std::endl;

void DefaultData(DataManager* dataManager);
void TestingStuffFunction();
int GetValidNumber(int low, int high, bool clear = false);
void MainMenu();
void AddFileMenu();
void ModifyAFile();

bool running = true;
DataManager* dataManager = new DataManager();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//TestingStuffFunction();
	cout << "Welcome to the Player Profile Database!\n";


	while (running)
	{
		MainMenu();
	}

	return 0;
}

void MainMenu()
{

	//DefaultData(dataManager);
	cout << "\n\nWhat would you like to do?\n";
	cout << "\t1. View All Records\n";
	cout << "\t2. Add A Record\n";
	cout << "\t3. Modify A Record\n";
	cout << "\t4. Find A Record (TBA)\n";
	cout << "\t5. Exit\n";
	switch (GetValidNumber(1, 5, true))
	{
	case 1:
		dataManager->PrintAll();
		break;
	case 2:
		AddFileMenu();
		break;
	case 3:
		ModifyAFile();
		break;
	case 4:
		break;
	case 5:
		running = false;
		break;
	}
}

int GetValidNumber(int low, int high, bool clear)
{
	int number;
	bool valid = false;
	while (!valid) {
		//cout << "Please enter a number between " << low << " and " << high << endl;
		cin >> number;
		if (number > high || number < low)
			cout << "Invalid input, try again!\n";
		else
			valid = true;
	}
	if (clear)
		system("cls");
	return number;

}

void AddFileMenu()
{
	PlayerData newEntry;

	char entryName[64];
	int highscore;

	cout << "Name of entry: ";
	cin >> entryName;
	cout << "\nHighscore: ";
	highscore = GetValidNumber(0, 999999999, false);

	newEntry.SetName(entryName);
	newEntry.SetHighscore(highscore);

	dataManager->AddFile(newEntry);
	dataManager->LoadAll();
	dataManager->SortData();
}

void ModifyAFile()
{
	cout << "Which entry would you like to modify?" << endl;
	int entryNo = GetValidNumber(0, dataManager->EntryCount(), false) - 1;
	PlayerData entry = dataManager->LoadProfile(entryNo);

	cout << "\nEntry Selected:";
	cout << "\n\tName: " << entry.GetName() << " | Highscore: " << entry.GetHighscore();

	char name[64];
	int highscore;

	cout << "\nEnter a new name: ";
	cin >> name;
	cout << "Enter a new highscore: ";
	highscore = GetValidNumber(0, 99999999, false);

	entry.SetName(name);
	entry.SetHighscore(highscore);

	dataManager->SaveProfile(entry, entryNo);
	dataManager->SortData();
	cout << "\nEntry Saved\n";
}

void DefaultData(DataManager* dataManager)
{
	const int dataEntries = 5;
	PlayerData** defaultData = new PlayerData * [dataEntries];
	defaultData[0] = new PlayerData();
	defaultData[1] = new PlayerData();
	defaultData[2] = new PlayerData();
	defaultData[3] = new PlayerData();
	defaultData[4] = new PlayerData();

	char name1[64] = "Jayden";
	char name2[64] = "Eric";
	char name3[64] = "Bob";
	char name4[64] = "Darren";
	char name5[64] = "Perkins";

	defaultData[0]->SetName(name1);
	defaultData[1]->SetName(name2);
	defaultData[2]->SetName(name3);
	defaultData[3]->SetName(name4);
	defaultData[4]->SetName(name5);

	defaultData[0]->SetHighscore(500);
	defaultData[1]->SetHighscore(1500);
	defaultData[2]->SetHighscore(2500);
	defaultData[3]->SetHighscore(300);
	defaultData[4]->SetHighscore(20000);


	dataManager->SaveAll(defaultData, dataEntries);
	dataManager->SortData();
}

void TestingStuffFunction()
{
	cout << "Welcome to the Player Profile Database!\n";
	DataManager* dataManager = new DataManager();

	//DefaultData(dataManager);

	std::cout << "LOADING DATA AND PRINTING IT!" << std::endl;
	PlayerData* data = dataManager->LoadAll();


	std::cout << "RETURNING DATA AND PRINTING IT!" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << data[i].GetName() << std::endl;

	}

	std::cout << "LOADING ENTRY 5 AND READING IT" << std::endl;

	PlayerData entry = dataManager->LoadProfile(4);
	std::cout << entry.GetName() << std::endl;

	std::cout << "CHANGING ENTRY 5's NAME TO DONKEY AND SAVING IT" << std::endl;
	char newName[64] = "DONKEY";
	entry.SetName(newName);


	dataManager->SaveProfile(entry, 4);
	std::cout << "RELOADING ENTRY 5 AND READING IT" << std::endl;

	entry = dataManager->LoadProfile(4);
	std::cout << entry.GetName() << std::endl;




	delete dataManager;
	dataManager = nullptr;
}