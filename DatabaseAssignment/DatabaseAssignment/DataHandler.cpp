#include "DataHandler.h"
#include "PlayerData.h"
#include <fstream>
#include <iostream>
#include <exception>

#define MEM_OFFSET sizeof(int)
#define PLAYER_SIZE sizeof(PlayerData)
#define FILE_DIR "players.dat"

DataHandler* DataHandler::handler = nullptr;

DataHandler::DataHandler()
{
	entryCount = 0;
	storedData = nullptr;
	LoadAllProfiles();
}

DataHandler::~DataHandler()
{
	//ClearData();
	
}

PlayerData DataHandler::LoadProfile(int entryPosition)
{
	if (entryPosition >= entryCount)
		return nullptr;

	PlayerData pData;

	std::fstream file;
	file.open(FILE_DIR, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{
		int offset = MEM_OFFSET + (entryPosition * PLAYER_SIZE);

		file.seekg(offset, std::ios::beg);

		if (!file.eof())
			file.read((char*)&pData, PLAYER_SIZE);

		file.close();
	}

	return pData;
}

void DataHandler::LoadAllProfiles()
{
	ClearData();

	std::fstream file;

	file.open(FILE_DIR, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{
		file.read((char*)&entryCount, sizeof(int));

		storedData = new PlayerData * [entryCount];

		for (int i = 0; i < entryCount; i++)
		{
			storedData[i] = new PlayerData();
		}

		for (int i = 0; i < entryCount; i++)
		{
			if (!file.eof())
			{
				PlayerData pData;
				file.read((char*)&pData, sizeof(PlayerData));

				storedData[i]->SetName((char*)pData.GetName());
				storedData[i]->SetHighscore(pData.GetHighscore());
			}
		}
		file.close();
	}

	SortData();
}

void DataHandler::SaveProfile(PlayerData* playerData, int entryPosition)
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary | std::ios_base::in);

	if (file.is_open())
	{
		int offset = MEM_OFFSET + (entryPosition * PLAYER_SIZE);

		file.seekp(offset, std::ios::beg);
		file.write((char*)&playerData, sizeof(PlayerData));
		file.close();
	}
}

void DataHandler::SaveAllProfiles()
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary);

	if (file.is_open())
	{
		file.write((char*)&entryCount, sizeof(int));

		for (int i = 0; i < entryCount; i++)
		{
			file.write((char*)storedData[i], PLAYER_SIZE);
		}
		file.close();
	}
}

void DataHandler::AddProfile(PlayerData& playerData)
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary | std::ios_base::app);

	if (file.is_open())
	{
		entryCount++;
		SetEntryCount();


		file.write((char*)&playerData, PLAYER_SIZE);
		file.close();

	}

	//LoadAllProfiles();
}

PlayerData* DataHandler::SearchProfile(const char* name)
{
	//Binary Search
	int min = 0;
	int max = entryCount - 1;
	bool resultFound = false;
	while (max > min)
	{
		int mid = (min + max) / 2;


		char compName[NAME_LENGTH];
		strcpy_s(compName, NAME_LENGTH, storedData[mid]->GetName());

		if (strcmp(name, compName) == 0)
			return storedData[mid];

		if (strcmp(name, compName) > 0)
			min = mid + 1;
		else
			max = mid - 1;
	}

	return nullptr;
}

void DataHandler::PrintAll()
{

	if (entryCount == 0)
	{
		std::cout << "\nNo entries found!\n";
	}

	for (int i = 0; i < entryCount; i++)
	{
		printf("Record Number %i: Name: %s | Highscore: %i\n", (i + 1), storedData[i]->GetName(), storedData[i]->GetHighscore());
	}
}

const int DataHandler::GetEntryCount()
{
	return entryCount;
}

DataHandler* DataHandler::Get()
{
	return handler;
}

void DataHandler::Create()
{
	if (DataHandler::handler)
		throw std::exception("Data handler already exists!");

	DataHandler::handler = new DataHandler();

}

void DataHandler::Release()
{
	if (!DataHandler::handler)
		return;
	DataHandler::handler->ClearData();
	delete DataHandler::handler;
	DataHandler::handler = nullptr;
}

void DataHandler::SetEntryCount()
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary | std::ios_base::in);

	if (file.is_open())
	{
		file.write((char*)&entryCount, MEM_OFFSET);
		file.close();
	}

}

void DataHandler::ClearData()
{
	if (storedData)
	{
		for (int i = 0; i < entryCount; i++)
		{
			if (storedData[i])
			{
				delete storedData[i];
				storedData[i] = nullptr;
			}
		}

		delete[] storedData;
		storedData = nullptr;
	}
}

void DataHandler::SortData()
{
	//Bubble Sort

	PlayerData temp;

	if (storedData && entryCount > 1)
	{
		for (int i = 0; i < entryCount - 1; i++)
		{
			for (int j = i + 1; j < entryCount; j++)
			{
				char name1[NAME_LENGTH];
				strcpy_s(name1, NAME_LENGTH, storedData[i]->GetName());
				char name2[NAME_LENGTH];
				strcpy_s(name2, NAME_LENGTH, storedData[j]->GetName());

				if (strcmp(name1, name2) > 0)
				{
					memcpy(&temp, storedData[i], PLAYER_SIZE);
					memcpy(storedData[i], storedData[j], PLAYER_SIZE);
					memcpy(storedData[j], &temp, PLAYER_SIZE);
				}
			}
		}
	}

	SaveAllProfiles();


}
