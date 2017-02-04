#include "RoomMap.h"
#include "NormalRoomFactory.h"
#include "MagicRoomFactory.h"

bool RoomMap::Initialize(std::string configFile)
{
	roomLibrary["Normal"] = (RoomFactory*)( new NormalRoomFactory());
	roomLibrary["Magic"] = (RoomFactory*)(new MagicRoomFactory());
	return this->LoadLevel(configFile.c_str());
}

Room* RoomMap::findNext(Room* room)
{
	return (room == NULL) ? rooms.find("start")->second : rooms.find(room->next())->second;
}

void RoomMap::randomizeRooms()
{

}

bool RoomMap::LoadLevel(const char* configFile)
{
	TiXmlDocument doc(configFile);
	if (!doc.LoadFile()) return false;

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem = hDoc.FirstChildElement().Element();
	if (!pElem) return false;
	hRoot = TiXmlHandle(pElem);

	TiXmlElement* RoomNode = hRoot.FirstChild("Room").Element();
	for (RoomNode; RoomNode; RoomNode = RoomNode->NextSiblingElement())
	{
		Room *new_room = roomLibrary[RoomNode->Attribute("type")]->create();
		new_room->Initialize(RoomNode);
		rooms[new_room->getIdentifier()] = new_room;
	}
	return true;
}