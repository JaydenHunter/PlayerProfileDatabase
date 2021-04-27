#include <fstream>
#include <iostream>
#include "DataManager.h"
#include "PlayerData.h"

#define MEM_OFFSET 4
#define FILE_DIR "data.dat"

DataManager::DataManager()
{
	entries = 0;
	storedData = LoadAll();
}

PlayerData DataManager::LoadProfile(int entryPosition)
{
	PlayerData data;

	std::fstream file;
	file.open(FILE_DIR, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{

		int offset = MEM_OFFSET + (entryPosition * sizeof(PlayerData));
		file.seekg(offset, std::ios::beg);

		if (!file.eof())
			file.read((char*)&data, sizeof(PlayerData));

		file.close();

	}
	return data;
}

PlayerData* DataManager::LoadAll()
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{
		file.read((char*)&entries, sizeof(int));

		PlayerData* data = new PlayerData[entries];

		for (int i = 0; i < entries; i++)
		{
			if (!file.eof())
			{
				PlayerData dataFile;
				file.read((char*)&dataFile, sizeof(PlayerData));

				data[i] = dataFile;
			}
		}

		file.close();
		if (data != nullptr)
			return data;
	}
	return nullptr;
}

void DataManager::SaveProfile(PlayerData playerData, int entryPosition)
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary | std::ios_base::in);

	if (file.is_open())
	{

		int offset = MEM_OFFSET + ((entryPosition) * sizeof(PlayerData));
		file.seekp(offset, std::ios::beg);

		//if (!file.eof())
		file.write((char*)&playerData, sizeof(PlayerData));

		file.close();

	}
}

void DataManager::SaveAll(PlayerData** playerData, int count)
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary);

	if (file.is_open())
	{
		//Store count at start for reading out in load
		file.write((char*)&count, sizeof(int));

		//Loop through all player data thats been saved
		for (int i = 0; i < count; i++)
		{
			file.write((char*)playerData[i], sizeof(PlayerData));

		}
		file.close();
	}
}

void DataManager::AddFile(PlayerData playerData)
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary | std::ios_base::app);
	if (file.is_open())
	{
		if (entries == 0)
		{
			file.write((char*)&entries, sizeof(int));
		}

		file.write((char*)&playerData, sizeof(PlayerData));
		file.close();
		entries++;
		ModifyEntryCount(entries);
	}
	storedData = LoadAll();

}
void DataManager::ModifyEntryCount(int newCount)
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary | std::ios_base::in );
	if (file.is_open())
	{
		file.write((char*)&newCount, sizeof(int));
		file.close();
	}
}
const int DataManager::EntryCount() {
	return entries;
}

void DataManager::PrintAll()
{
	storedData = LoadAll();
	for (int i = 0; i < entries; i++)
	{
		std::cout << "Record Number " << (i + 1) << ": Name: " << storedData[i].GetName() << " \t| Highscore: " << storedData[i].GetHighscore() << std::endl;
	}
}
