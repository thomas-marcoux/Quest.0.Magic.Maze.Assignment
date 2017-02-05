#ifndef NORMALROOM_H
#define NORMALROOM_H

#include "Room.h"

//Child of Room, implements the execute virtual method.
class NormalRoom : Room
{
public:
	Room* execute(RoomMap*, int &);
};

#endif