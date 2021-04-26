#include <fstream>
#include <iostream>
#include "DataManager.h"
#include "PlayerData.h"


DataManager::DataManager()
{
	PlayerData* storedData = LoadProfile();
}

PlayerData* DataManager::LoadProfile()
{
	return nullptr;
}

PlayerData* DataManager::LoadAll()
{
	PlayerData** data = new PlayerData*[1];

	std::fstream file;
	file.open("data.dat", std::ios_base::in | std::ios_base::binary);
	if (file.is_open())
	{
		int* count;
		//file.read((char*)&count, sizeof(int));

		data = new PlayerData*[3];
		data[0] = new PlayerData();
		data[1] = new PlayerData();
		data[2] = new PlayerData();
		int counter = 0;
		while (!file.eof() && file.peek() != EOF)
		{
			PlayerData* dataFile;
			file.read((char*)&dataFile, sizeof(PlayerData));
			//std::cout << *data[counter]->GetName() << std::endl;
			data[counter] = dataFile;
			counter++;
		}
		
	}
	file.close();
	if (data != nullptr)
		return *data;
	else
		return nullptr;
}

void DataManager::SaveProfile(PlayerData playerData)
{

}

void DataManager::SaveAll(PlayerData* playerData, int count)
{
	std::fstream file;
	file.open("data.dat", std::ios_base::out | std::ios_base::binary);
	if (file.is_open())
	{
		//Store count at start for reading out in load
		//file.write((char*)&count, sizeof(int));

		//Loop through all player data thats been saved
		for (int i = 0; i < count; i++)
		{
			file.write((char*)&playerData[i], sizeof(PlayerData));
		}
		
	}
	file.close();
}