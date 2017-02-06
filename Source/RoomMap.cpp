#include <algorithm>
#include<iostream>
#include <random>
#include <vector>
#include "RoomMap.h"
#include "NormalRoomFactory.h"
#include "MagicRoomFactory.h"

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

//Initializes the items and randomizes their distribution.
RoomMap::RoomMap()
{
	itemBank.push_back("Map");
	itemBank.push_back("Compass");
	itemBank.push_back("Boomerang");
	itemBank.push_back("Bomb");
	itemBank.push_back("Sword");
	itemBank.push_back("Armor");
	itemBank.push_back("Potion");
	itemBank.push_back("Hook");
	itemBank.push_back("Money");
	randomize();
	std::shuffle(itemBank.begin(), itemBank.end(), global_urng());
}

/*
Initializes the roomLibrary with factory classes and load the level
from a xml file. Assigns items to the rooms.
Returns false is the file could not be loaded.
*/
bool RoomMap::Initialize(std::string configFile)
{
	roomLibrary["Normal"] = (RoomFactory*)( new NormalRoomFactory());
	roomLibrary["Magic"] = (RoomFactory*)(new MagicRoomFactory());
	if (!this->LoadLevel(configFile.c_str()))
		return false;
	for (auto &room : rooms)
	{
		if (!itemBank.empty())
		{
			roomInventory[room.first] = itemBank.back();
			itemBank.pop_back();
		}
		else
			roomInventory[room.first] = "";
	}
	return true;
}

//Checks if the player has collected the item assigned to the current room
bool	RoomMap::hasItem(Room* room)
{
	return (playerInventory.find(room->getIdentifier()) == playerInventory.end()) ? false : true;
}

//Add item to the player's inventory
void	RoomMap::addItem(Room* room)
{
	playerInventory[room->getIdentifier()] = roomInventory.find(room->getIdentifier())->second;
	roomInventory[room->getIdentifier()] = "";
}

//Print out the player inventory
void	RoomMap::showInventory()
{
	for (auto &item : playerInventory)
		std::cout << item.second << " ";
	std::cout << std::endl;
}

//Empties the player's inventory and distributes it amongst empty rooms
void	RoomMap::emptyInventory()
{
	for (auto &item : playerInventory)
		itemBank.push_back(item.second);
	playerInventory.clear();
	randomize();
	std::shuffle(itemBank.begin(), itemBank.end(), global_urng());
	for (auto &room : roomInventory)
	{
		if (room.second == "")
		{ 
			roomInventory[room.first] = itemBank.back();
			itemBank.pop_back();
		}
	}
}

//Save the state of the game to a xml file
bool	RoomMap::saveState(Room* room, int &health)
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	TiXmlElement * root = new TiXmlElement("Save");
	TiXmlComment * comment = new TiXmlComment();
	TiXmlElement * player = new TiXmlElement("Player Data");
	TiXmlElement * inventory = new TiXmlElement("Inventory");
	TiXmlElement* item;

	doc.LinkEndChild(decl);
	doc.LinkEndChild(root);
	comment->SetValue("Player State");
	root->LinkEndChild(comment);


	root->LinkEndChild(inventory);

	item = new TiXmlElement("Welcome");
	item->LinkEndChild(new TiXmlText("Welcome to MyApp"));
	item->SetAttribute("x", 5);
	inventory->LinkEndChild(item);

	doc.SaveFile("save.xml");
	return true;
}

//Load the saved state
bool	RoomMap::loadState()
{
	return true;
}

//Returns the next room in the map from room's next method.
Room* RoomMap::findNext(Room* room)
{
	return (room == NULL) ? rooms.find("start")->second : rooms.find(room->next())->second;
}

//Shuffles the rooms with the exception of the "quit" room.
void RoomMap::randomizeRooms()
{
	std::vector<Room*>	buff;

	for (auto &room : rooms)
	{
		if (room.first != "quit")
			buff.push_back(room.second);
	}
	randomize();
	std::shuffle(buff.begin(), buff.end(), global_urng());
	for (auto &room : rooms)
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
	TiXmlHandle headDoc(&doc);
	TiXmlElement* elem;
	TiXmlHandle root(0);

	//Sets the root
	elem = headDoc.FirstChildElement().Element();
	if (!elem) return false;
	root = TiXmlHandle(elem);
	//Browse all "Room" tags in the file.
	TiXmlElement* RoomNode = root.FirstChild("Room").Element();
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