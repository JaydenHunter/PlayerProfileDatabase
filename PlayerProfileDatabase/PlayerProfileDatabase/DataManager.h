#pragma once
class PlayerData;

class DataManager
{
public:
	DataManager();
	PlayerData* LoadProfile();
	PlayerData* LoadAll();
	void SaveProfile(PlayerData playerData);
	void SaveAll(PlayerData* playerData, int count);
private:
	PlayerData* storedData;
};

