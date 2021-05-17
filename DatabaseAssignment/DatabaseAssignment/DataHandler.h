#pragma once
class PlayerData;
//-------------------------------------------
// Handles all functions related to modifying
// and removing Player profiles
//-------------------------------------------
class DataHandler
{
public:
	//Constructor & Destructor
	DataHandler();

	//Loading Functions
	PlayerData LoadProfile(int entryPosition);
	void LoadAllProfiles();

	//Saving Functions
	void SaveProfile(PlayerData* playerData, int entryPosition);
	void SaveAllProfiles();
	
	//Adding and Searching
	void AddProfile(PlayerData& playerData);
	PlayerData* SearchProfile(const char* name);

	void PrintAll();
	const int GetEntryCount();
	
	
public:
	//Functions for singleton Use
	static DataHandler* Get(); 
	static void Create();
	static void Release();
	

private:
	//Data modification and clearing
	void SetEntryCount();
	void SortData();
	void ClearData();

private:
	int entryCount;
	PlayerData** storedData;

	//Singleton reference
	static DataHandler* handler;

};

