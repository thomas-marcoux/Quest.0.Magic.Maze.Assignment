#include<iostream>
#include "MagicRoom.h"
#include "RoomMap.h"

Room * MagicRoom::execute(RoomMap *map, int &health)
{
	std::cout << "You hear loud grinding sounds and you feel your strength restored!" << std::endl;
	health += 2;
	map->randomizeRooms();
	std::cout << "View: " << description << std::endl;
	std::cout << "Health: " << health << std::endl;
	std::cout << "Available moves:";
	for (auto neighbor : neighbors)
	{
		std::cout << " " << neighbor.first;
	}
	std::cout << std::endl << "Select move: " << std::endl;
	std::cin >> transition;
	return map->findNext(this);
}
