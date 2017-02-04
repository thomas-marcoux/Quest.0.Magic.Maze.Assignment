#include "Room.h"

bool Room::Initialize(TiXmlElement* RoomNode)
{
	TiXmlElement* NeighborNode = TiXmlHandle(RoomNode).FirstChild().Element();
	condition = (END_CONDITION)atoi(RoomNode->Attribute("condition"));
	identifier = RoomNode->Attribute("name");
	description = RoomNode->Attribute("description");
	for (NeighborNode; NeighborNode; NeighborNode = NeighborNode->NextSiblingElement())
	{
		this->addNeighbor(NeighborNode->Attribute("transition"), NeighborNode->Attribute("target"));
	}
	return true;
}

bool Room::finish()
{
	return (condition == NONE) ? false : true;
}

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