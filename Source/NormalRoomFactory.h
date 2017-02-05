#ifndef NORMALROOMFACTORY_H
#define NORMALROOMFACTORY_H

#include "NormalRoom.h"

//Creates NormalRoom objects.
class NormalRoomFactory : RoomFactory
{
public:
	Room* create() { return (Room*)(new NormalRoom()); }
};

#endif