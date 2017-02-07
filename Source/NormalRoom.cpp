#include "NormalRoom.h"

/*
The NormalRoom's execute function displays information,
updates player health and inventory, and prompts the user for input
while checking that the input is valid.
It returns the next room.
*/
Room * NormalRoom::execute(RoomMap *map, int &health)
{
	std::string	input = "";

	//Pick up room item if the player does not have it already.
	if (!map->hasItem(this))
		map->addItem(this);
	input = showPlayerInterface(map, health);
	if (input == "load")
		return map->loadState(this, health);
	transition = input;
	--health;
	return map->findNext(this);
}
