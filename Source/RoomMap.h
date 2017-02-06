#ifndef ROOMMAP_H
#define ROOMMAP_H

#include<map>
#include<string>
#include<vector>

#include"Room.h"
#include"RoomFactory.h"

#include"ThirdParty\tinyxml\tinystr.h"
#include"ThirdParty\tinyxml\tinyxml.h"

//Room container
class RoomMap
{
public:
	RoomMap();
	bool Initialize(std::string configFile);
	Room* findNext(Room*); 
	void randomizeRooms();
	bool hasItem(Room*);
	void addItem(Room*);
	void showInventory();
	void emptyInventory();
	bool saveState(Room*, int&);
	Room* loadState(Room*, int&);

private:
	std::map<std::string,RoomFactory*> roomLibrary;
	std::map<std::string,Room*> rooms;
	std::map<std::string, std::string> playerInventory;
	std::map<std::string, std::string> roomInventory;
	std::vector<std::string> itemBank;

	//Private XML level loading instructions
	bool RoomMap::LoadLevel(const char* configFile);
	//Private inventory loading/saving instructions
	bool RoomMap::loadInventory(TiXmlElement*,std::map<std::string, std::string>&);
	bool RoomMap::saveInventory(TiXmlElement*, std::map<std::string, std::string>&);
};

#endif