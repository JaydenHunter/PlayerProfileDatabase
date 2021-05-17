#include <crtdbg.h>
#include "DataHandler.h"
#include "PlayerData.h"
#include "Menu.h"

void DefaultData();


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		DataHandler::Create();
	}
	catch (...) { return -1; }
	//DefaultData();
	DataHandler::Get()->LoadAllProfiles();
	try
	{
		Menu menu;
		menu.MenuLoop();
	}
	catch (...)
	{
		DataHandler::Release();
		return -1;
	}

	DataHandler::Release();
	
	return 0;
}

void DefaultData()
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

	for (int i = 0; i < dataEntries; i++)
	{
		if (defaultData[i])
		{
			DataHandler::Get()->AddProfile(*defaultData[i]);

			delete defaultData[i];
			defaultData[i] = nullptr;
		}
	}

	delete[] defaultData;
	defaultData = nullptr;

}