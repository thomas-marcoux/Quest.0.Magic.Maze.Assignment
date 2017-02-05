#ifndef MAGICROOMFACTORY_H
#define MAGICROOMFACTORY_H

#include "MagicRoom.h"

//Creates MagicRoom objects
class MagicRoomFactory : RoomFactory
{
public:
	Room* create() { return (Room*)(new MagicRoom()); }
};

#endif