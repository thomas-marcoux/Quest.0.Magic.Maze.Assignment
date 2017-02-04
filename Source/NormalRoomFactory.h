#ifndef NORMALROOMFACTORY_H
#define NORMALROOMFACTORY_H

#include "NormalRoom.h"

class NormalRoomFactory : RoomFactory
{
public:
	Room* create() { return (Room*)(new NormalRoom()); }
};

#endif