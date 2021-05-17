#include "DataHandler.h"
#include "PlayerData.h"
#include <fstream>
#include <iostream>
#include <exception>

#define MEM_OFFSET sizeof(int)
#define PLAYER_SIZE sizeof(PlayerData)
#define FILE_DIR "players.dat"

//Singleton Reference
DataHandler* DataHandler::handler = nullptr;

//--------------------------------------
// Constructor
//--------------------------------------
DataHandler::DataHandler()
{
	entryCount = 0;
	storedData = nullptr;
	LoadAllProfiles();
}

//--------------------------------------
// Returns a profile from a given position in the file
//--------------------------------------
PlayerData DataHandler::LoadProfile(int entryPosition)
{
	if (entryPosition >= entryCount || entryPosition < 0) //Check that the desired position is within range
		return nullptr;

	PlayerData pData;

	std::fstream file;
	file.open(FILE_DIR, std::ios_base::in | std::ios_base::binary);
	//Open file and seek to position
	//Read out data into a PlayerData class
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

//--------------------------------------
// Loads all profile data into the storedData
//--------------------------------------
void DataHandler::LoadAllProfiles()
{
	ClearData(); //Clear all current data that is stored

	std::fstream file;

	file.open(FILE_DIR, std::ios_base::in | std::ios_base::binary);
	//Open up file and read in the player data
	if (file.is_open())
	{
		//Get the amount of entries we need to load in
		file.read((char*)&entryCount, sizeof(int));

		//Initialize the PlayerData classes
		storedData = new PlayerData * [entryCount];

		for (int i = 0; i < entryCount; i++)
		{
			storedData[i] = new PlayerData();
		}
		//Loop through all entries and read them in
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

//--------------------------------------
// Saves a single profile in the file
//--------------------------------------
void DataHandler::SaveProfile(PlayerData* playerData, int entryPosition)
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary | std::ios_base::in);

	//Seek position in file and write to the data
	if (file.is_open())
	{
		int offset = MEM_OFFSET + (entryPosition * PLAYER_SIZE);

		file.seekp(offset, std::ios::beg);
		file.write((char*)&playerData, sizeof(PlayerData));
		file.close();
	}
}

//--------------------------------------
// Saves all storedData profiles into the file
//--------------------------------------
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

//--------------------------------------
// Adds a new profile to file and reloads
//--------------------------------------
void DataHandler::AddProfile(PlayerData& playerData)
{
	std::fstream file;
	file.open(FILE_DIR, std::ios_base::out | std::ios_base::binary | std::ios_base::app);

	if (file.is_open())
	{
		//Update entry count in file
		entryCount++;
		SetEntryCount();

		//Reverse count for when profiles are reloaded
		entryCount--;

		file.write((char*)&playerData, PLAYER_SIZE);
		file.close();
	}

	//Reload files into Stored Data
	LoadAllProfiles();
}

//--------------------------------------
// Searches for a specific profile in the stored data
//--------------------------------------
PlayerData* DataHandler::SearchProfile(const char* name)
{
	//Binary Search
	int min = 0;
	int max = entryCount - 1;
	while (min <= max)
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

//--------------------------------------
// Print out all Player Profiles to console
//--------------------------------------
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

//--------------------------------------
// Gets count of all entries
//--------------------------------------
const int DataHandler::GetEntryCount()
{
	return entryCount;
}

//--------------------------------------
// Returns singleton Instance
//--------------------------------------
DataHandler* DataHandler::Get()
{
	return handler;
}

//--------------------------------------
// Creates singleton instance if it hasn't been created
//--------------------------------------
void DataHandler::Create()
{
	if (DataHandler::handler)
		throw std::exception("Data handler already exists!");

	DataHandler::handler = new DataHandler();

}

//--------------------------------------
// Releases all memory that was occupied 
//--------------------------------------
void DataHandler::Release()
{
	if (!DataHandler::handler)
		return;
	DataHandler::handler->ClearData();
	delete DataHandler::handler;
	DataHandler::handler = nullptr;
}

//--------------------------------------
// Modify the count of entries in the file
//--------------------------------------
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

//--------------------------------------
// Clears up memory usage of the stored data
//--------------------------------------
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

//--------------------------------------
// Sorts Player Profiles in ascending order by name
//--------------------------------------
void DataHandler::SortData()
{
	//Bubble Sort

	PlayerData temp;

	if (storedData && entryCount > 1)
	{
		for (int i = 0; i < entryCount - 1; i++)
		{
			char name1[NAME_LENGTH];
			strcpy_s(name1, NAME_LENGTH, storedData[i]->GetName());

			for (int j = i + 1; j < entryCount; j++)
			{
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
