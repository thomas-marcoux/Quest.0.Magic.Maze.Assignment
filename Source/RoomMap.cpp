#include <algorithm>
#include <random>
#include <vector>
#include "RoomMap.h"
#include "NormalRoomFactory.h"
#include "MagicRoomFactory.h"

/*
Initializes the roomLibrary with factory classes and load the level
from a xml file.
Returns false is the file could not be loaded.
*/
bool RoomMap::Initialize(std::string configFile)
{
	roomLibrary["Normal"] = (RoomFactory*)( new NormalRoomFactory());
	roomLibrary["Magic"] = (RoomFactory*)(new MagicRoomFactory());
	return this->LoadLevel(configFile.c_str());
}

//Returns the next room in the map from room's next method.
Room* RoomMap::findNext(Room* room)
{
	return (room == NULL) ? rooms.find("start")->second : rooms.find(room->next())->second;
}

//Sets a single URNG.
std::default_random_engine&	global_urng()
{
	static std::default_random_engine  u{};
	return u;
}

//Sets the shared URNG to an unpredictable state.
void	randomize()
{
	static std::random_device	rd{};
	global_urng().seed(rd());
}

//Shuffles the rooms with the exception of the "quit" room.
void RoomMap::randomizeRooms()
{
	std::vector<Room*>	buff;

	for (auto room : rooms)
	{
		if (room.first != "quit")
			buff.push_back(room.second);
	}
	randomize();
	std::shuffle(buff.begin(), buff.end(), global_urng());
	for (auto room : rooms)
	{
		if (room.first != "quit")
		{
			rooms[room.first] = buff.back();
			buff.pop_back();
		}
	}
}

/*
Loads configFile and passes Room elements to the Initialize method
of each room object created with the room factory.
Returns false is the loading fails.
*/
bool RoomMap::LoadLevel(const char* configFile)
{
	std::string	type;
	TiXmlDocument doc(configFile);
	if (!doc.LoadFile()) return false;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	//Sets the root
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem) return false;
	hRoot = TiXmlHandle(pElem);
	//Browse all "Room" tags in the file.
	TiXmlElement* RoomNode = hRoot.FirstChild("Room").Element();
	if (!RoomNode) return false;
	for (RoomNode; RoomNode; RoomNode = RoomNode->NextSiblingElement())
	{
		type = RoomNode->Attribute("type");
		//Checks that the type exists and is contained in the roomLibrary
		if (roomLibrary.find(type) == roomLibrary.end()) return false;
		Room *new_room = roomLibrary[type]->create();
		if (!new_room->Initialize(RoomNode)) return false;
		rooms[new_room->getIdentifier()] = new_room;
	}
	return true;
}