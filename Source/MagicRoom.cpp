#include "MagicRoom.h"

/*
The MagicRoom's execute function displays information,
updates player health, empties inventory, randomizes the rooms
and prompts the user for input
while checking that the input is valid.
It returns the next room.
*/
Room * MagicRoom::execute(RoomMap *map, int &health)
{
	std::string	input = "";

	std::cout << "You hear loud grinding sounds and you feel your strength restored!" << std::endl;
	health += 2;
	map->emptyInventory();
	map->randomizeRooms();
	input = showPlayerInterface(map, health);
	if (input == "load")
		return map->loadState(this, health);
	transition = input;
	return map->findNext(this);
}
