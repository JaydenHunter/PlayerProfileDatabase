#include <iostream>
#include "DataManager.h"
using std::cin;
using std::cout;
using std::endl;

int main()
{
	cout << "Welcome to the Player Profile Database!\n";
	DataManager* dataManager = new DataManager();

	dataManager->LoadAll();
	return 0;
}