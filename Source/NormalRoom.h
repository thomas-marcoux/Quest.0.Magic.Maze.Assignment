#ifndef NORMALROOM_H
#define NORMALROOM_H

#include "Room.h"

class NormalRoom : Room
{
public:
	Room* execute(RoomMap*, int &);
};

#endif