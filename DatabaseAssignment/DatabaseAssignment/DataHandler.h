#pragma once
class PlayerData;

class DataHandler
{
public:
	DataHandler();
	~DataHandler();

	PlayerData LoadProfile(int entryPosition);
	void LoadAllProfiles();

	void SaveProfile(PlayerData* playerData, int entryPosition);
	void SaveAllProfiles();
	
	void AddProfile(PlayerData& playerData);

	PlayerData* SearchProfile(const char* name);
	void PrintAll();

	const int GetEntryCount();

public:
	static DataHandler* Get();
	static void Create();
	static void Release();
	
private:
	void SetEntryCount();
	void ClearData();
	void SortData();

private:
	int entryCount;
	PlayerData** storedData;

	static DataHandler* handler;

};

