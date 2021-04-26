#pragma once
class PlayerData;

class DataManager
{
public:
	DataManager();
	PlayerData* LoadProfile();
	PlayerData* LoadAll();
	void SaveProfile(PlayerData playerData);
	void SaveAll(PlayerData* playerData);
private:
	PlayerData* storedData;
};

