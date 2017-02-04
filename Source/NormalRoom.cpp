#include<iostream>
#include "NormalRoom.h"
#include "RoomMap.h"

Room * NormalRoom::execute(RoomMap *map, int &health)
{
	std::cout << "View: " << description << std::endl;
	std::cout << "Health: " << health << std::endl;
	std::cout << "Available moves:";
	for (auto neighbor : neighbors)
	{
		std::cout << " " << neighbor.first;
	}
	std::cout << std::endl << "Select move: " << std::endl;
	std::cin >> transition;
	--health;
	return map->findNext(this);
}
