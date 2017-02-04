#ifndef ROOMMAP_H
#define ROOMMAP_H

#include<map>
#include<string>

#include"Room.h"
#include"RoomFactory.h"

#include"ThirdParty\tinyxml\tinystr.h"
#include"ThirdParty\tinyxml\tinyxml.h"

class RoomMap
{
public:
	RoomMap();
	bool Initialize(std::string configFile);
	Room* findNext(Room*); 
	void randomizeRooms();

private:
	std::map<std::string,RoomFactory*> roomLibrary;
	std::map<std::string,Room*> rooms;

	//Private XML level loading instructions
	bool RoomMap::LoadLevel(const char* configFile);
};

#endif