#include <iostream>
#include <set>
#include "NormalRoom.h"
#include "RoomMap.h"

/*
The NormalRoom's execute function displays information,
updates player health and inventory, and prompts the user for input
while checking that the input is valid.
It returns the next room.
*/
Room * NormalRoom::execute(RoomMap *map, int &health)
{
	std::string	input = "";
	std::set<std::string>	possible_moves;

	std::cout << "View: " << description << std::endl;
	std::cout << "Health: " << health << std::endl;
	if (!map->hasItem(this))
		map->addItem(this);
	std::cout << "Inventory: ";
	map->showInventory();
	//Stores possible moves in a set
	for (auto neighbor : neighbors)
		possible_moves.insert(neighbor.first);
	//Checks that the input is a valid move
	while (possible_moves.find(input) == possible_moves.end())
	{
		std::cout << "Available moves:";
		for (auto move : possible_moves)
			std::cout << " " << move;
		std::cout << std::endl << "Select move: " << std::endl;
		std::cin >> input;
	}
	transition = input;
	--health;
	return map->findNext(this);
}
