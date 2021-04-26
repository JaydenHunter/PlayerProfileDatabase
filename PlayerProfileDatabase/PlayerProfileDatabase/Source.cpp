#include <iostream>
#include "DataManager.h"
#include "PlayerData.h"
using std::cin;
using std::cout;
using std::endl;

void DefaultData(DataManager* dataManager)
{
	PlayerData** defaultData = new PlayerData * [3];
	defaultData[0] = new PlayerData();
	defaultData[1] = new PlayerData();
	defaultData[2] = new PlayerData();

	char name1[64] = "Jayden";
	char name2[64] = "Eric";
	char name3[64] = "Bob";

	defaultData[0]->SetName(name1);
	defaultData[1]->SetName(name2);
	defaultData[2]->SetName(name3);

	defaultData[0]->SetHighscore(500);
	defaultData[1]->SetHighscore(1500);
	defaultData[2]->SetHighscore(2500);

	dataManager->SaveAll(*defaultData, 3);
}

int main()
{
	cout << "Welcome to the Player Profile Database!\n";
	DataManager* dataManager = new DataManager();
	DefaultData(dataManager);
	PlayerData* data = dataManager->LoadAll();
	std::cout << data[0].GetName();


	return 0;
}