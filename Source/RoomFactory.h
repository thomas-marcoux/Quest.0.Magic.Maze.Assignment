#ifndef ROOMFACTORY_H
#define ROOMFACTORY_H

#include "Room.h"

//Object factory creating normal or magic rooms.
class RoomFactory
{
public:
	virtual Room* create() = 0;
};

#endif