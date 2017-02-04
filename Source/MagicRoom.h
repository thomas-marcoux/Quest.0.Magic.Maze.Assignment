#ifndef MAGICROOM_H
#define MAGICROOM_H

#include "Room.h"

class MagicRoom : Room
{
public:
	Room* execute(RoomMap*, int &);
};

#endif