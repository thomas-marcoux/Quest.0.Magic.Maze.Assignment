#ifndef ROOMFACTORY_H
#define ROOMFACTORY_H

#include "Room.h"

class RoomFactory
{
public:
	virtual Room* create() = 0;
};

#endif