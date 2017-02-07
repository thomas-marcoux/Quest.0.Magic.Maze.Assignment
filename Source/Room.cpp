#include <iostream>
#include <set>
#include "Room.h"

/*
Initializes Room attributes from XML.
Returns false if loading was unsuccessful.
*/
bool Room::Initialize(TiXmlElement* RoomNode)
{
	const char *attr_condition, *attr_identifier, *attr_description, *attr_transition, *attr_target;
	TiXmlElement* NeighborNode = TiXmlHandle(RoomNode).FirstChild().Element();

	attr_condition = RoomNode->Attribute("condition");
	attr_identifier = RoomNode->Attribute("name");
	attr_description = RoomNode->Attribute("description");
	//Verifies the existence of each attribute.
	if (!attr_condition || !attr_identifier || !attr_description) return false;
	condition = (END_CONDITION)atoi(attr_condition);
	identifier = attr_identifier;
	description = attr_description;
	for (NeighborNode; NeighborNode; NeighborNode = NeighborNode->NextSiblingElement())
	{
		attr_transition = NeighborNode->Attribute("transition");
		attr_target = NeighborNode->Attribute("target");
		//Verifies the existence of each attribute.
		if (!attr_transition || !attr_target) return false;
		this->addNeighbor(attr_transition, attr_target);
	}
	return true;
}

//Displays player information and prompts for input
std::string Room::showPlayerInterface(RoomMap* map, int &health)
{
	std::string	input = "";
	std::set<std::string>	possible_moves;

	std::cout << "View: " << description << std::endl;
	std::cout << "Health: " << health << std::endl;
	std::cout << "Inventory: ";
	map->showInventory();
	//Stores possible moves in a set
	for (auto neighbor : neighbors)
		possible_moves.insert(neighbor.first);
	//Checks that the input is a valid move
	while (possible_moves.find(input) == possible_moves.end())
	{
		std::cout << "Available moves:";
		for (auto move : possible_moves)
			std::cout << " " << move;
		std::cout << std::endl << "Select move: " << std::endl;
		std::cin >> input;
		if (input == "save")
			map->saveState(this, health);
		if (input == "load")
			return input;
	}
	return input;
}

//Returns a boolean indicating whether the game is over.
bool Room::finish()
{
	return (condition == NONE) ? false : true;
}

//Returns the identifier of the destination room.
std::string Room::next()
{
	return neighbors.find(transition)->second;
}

//Accessor methods
void Room::setIdentifier(std::string new_identifier)
{
	identifier = new_identifier;
}

void Room::setDescription(std::string new_description)
{
	description = new_description;
}

std::string Room::getIdentifier()
{
	return identifier;
}

END_CONDITION Room::getCondition()
{
	return condition;
}

void  Room::addNeighbor(std::string new_transition, std::string new_identifier)
{
	neighbors.insert(std::pair<std::string, std::string>(new_transition, new_identifier));
}