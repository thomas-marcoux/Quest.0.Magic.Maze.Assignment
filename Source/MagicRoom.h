#ifndef MAGICROOM_H
#define MAGICROOM_H

#include "Room.h"

//Child of Room, adds extra features to the execute method.
class MagicRoom : Room
{
public:
	Room* execute(RoomMap*, int &);
};

#endif