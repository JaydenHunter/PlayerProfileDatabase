#pragma once
class PlayerData;

class DataManager
{
public:
	DataManager();
	PlayerData LoadProfile(int entryPosition);
	PlayerData* LoadAll();
	void SaveProfile(PlayerData playerData,int entryPosition);
	void SaveAll(PlayerData** playerData, int count);
	void AddFile(PlayerData playerData);
	void PrintAll();
	const int EntryCount();

private:
	int entries;
	PlayerData* storedData;

	void ModifyEntryCount(int newCount);
};

