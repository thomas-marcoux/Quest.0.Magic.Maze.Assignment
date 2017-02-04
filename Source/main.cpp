/*
* Author:	Keith Bush
*			UALR
* 
* Date:		January 27, 2015	
*
* File:		main.cpp
*
* Purpose:	The purpose of this homework is to explore the use of the Object Factory design
*           pattern in combination with XML parsing for configuration
*/

#include<iostream>
#include "RoomMap.h"
#include "Room.h"

//using namespace std;

//GUI Helper Functions
void clearConsole();
void pauseConsole();
void splashScreen();

//Engine Functions
bool isGameDone(Room*, int);
void displayGameDone(Room*, int);

int main()
{

	//Declare Game Space
	RoomMap* map = NULL;
	Room* room = NULL;
	int health = -1;  //Need to wrap this in somehting

	//Initialize Resource Management
	map = new RoomMap();
	map->Initialize("./Config/puzzle.xml");

	//Initialize Game State
	room = map->findNext(room);
	health = 10;	

	//Splash Screen
	clearConsole();
	splashScreen();

	//Until Game Termination Condition Do:
	while(!isGameDone(room,health))
	{

		//Wipe the GUI clean
		clearConsole();

		//Perform the game mechanic
		room = room->execute(map, health);

	}

	//Display End Game State
	displayGameDone(room,health);

	return 0;

}


void clearConsole()
{
	system("cls");
}

void pauseConsole()
{
	system("PAUSE");
}

void splashScreen()
{
	std::cout << "ROOM PUZZLE" << std::endl;
	std::cout << std::endl;
	std::cout << "Your name here (2015)" << std::endl;
	std::cout << "CPSC 4399/4399, Advanced Game Programming, Homework 0" << std::endl;
	std::cout << "UALR, Computer Science Dept." << std::endl;
	std::cout << std::endl;
	std::cout << "INSTRUCTIONS: Find the finish!" << std::endl;
	std::cout << std::endl;
	pauseConsole();
}

void displayGameDone(Room* room, int health){

	clearConsole();

	if(health <= 0)
	{
			std::cout << std::endl;
			std::cout << "GAME OVER..." << std::endl;
			std::cout << std::endl;
	}
	else
	{
		switch(room->getCondition())
		{
		case WIN:
			std::cout << std::endl;
			std::cout << "YOU WIN" << std::endl;
			std::cout << std::endl;
			break;
		case LOSE:
			std::cout << std::endl;
			std::cout << "GAME OVER..." << std::endl;
			std::cout << std::endl;
			break;
		case QUIT:
			std::cout << std::endl;
			std::cout << "GOOD BYE" << std::endl;
			std::cout << std::endl;
			break;
		}
	}

	pauseConsole();	

}

bool isGameDone(Room* room, int health){

	if(room->finish() || health <= 0)
	{
		return(true);
	}
	else
	{
		return(false);
	}

}
