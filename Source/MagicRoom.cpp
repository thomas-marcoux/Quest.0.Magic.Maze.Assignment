#include <iostream>
#include <set>
#include "MagicRoom.h"
#include "RoomMap.h"

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
	std::set<std::string>	possible_moves;

	std::cout << "You hear loud grinding sounds and you feel your strength restored!" << std::endl;
	health += 2;
	map->randomizeRooms();
	std::cout << "View: " << description << std::endl;
	std::cout << "Health: " << health << std::endl;
	map->emptyInventory();
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
	return map->findNext(this);
}
