#include <utility>
#include <iostream> 
#include <string> 
#include <map>
#include <stdio.h>
#include <string.h>
#include "game/Board.hpp"
#include "./game/Gomoku.hpp"
#include "engine/CoreEngine.hpp"
#include <unistd.h>

Gomoku		*parsingParameters(int ac, char **av)
{
	int opt = 0;
	Gomoku *gomoku = new Gomoku();
	while ( (opt = getopt(ac, av, "damh")) != -1 ) 
	{
		switch ( opt ) 
		{
			case 'd':
				gomoku->setVerbose(true);
			break;
			case 'a':
				gomoku->setAssist(true);
			break;
			case 'm':
				gomoku->setGameMode(-1);
			break;
			case 'h':
				std::cout << "Gomoku is an awesome game, where you lose alsmost every time, just launch it, then press y and enter to play against the computer" << std::endl;
				std::cout << "-d : to display debug to understand how the IA algorithm works" << std::endl;
				std::cout << "-a : to get help if you don't know how to play" << std::endl;
				std::cout << "-m : to choose game mode" << std::endl;
				std::cout << "-h : display help" << std::endl;
			break;
			case '?':
				std::cout << "Unknown option: '" << char(optopt) << "'!" << std::endl;
			break;
		}
	}
	return gomoku;
}

void		displayInformation(Gomoku *gomoku)
{
	if (gomoku->getVerbose())
		std::cout << "Verbose mode ON" << std::endl;
	else
		std::cout << "Verbose mode OFF" << std::endl;
	if (gomoku->getAssist())
		std::cout << "Assist mode ON" << std::endl;
	else
		std::cout << "Assist mode OFF" << std::endl;

	if (gomoku->getGameMode() == 1)
		std::cout << "Game Mode: Swap 1" << std::endl;
	else if (gomoku->getGameMode() == 2)
		std::cout << "Game Mode: Swap 2" << std::endl;
	else
		std::cout << "Game Mode: Default" << std::endl;

}

int			selectGameMode( void )
{
	int i;
	char buffer[256];

	std::cout << "Select Game Starting Rule" << std::endl;
	std::cout << "0 - default" << std::endl;
	std::cout << "1 - Swap 1" << std::endl;
	std::cout << "2 - Swap 2" << std::endl;
	std::cout << "please select mode: ";
	fgets (buffer, 256, stdin);
	i = atoi(buffer);
	if (i == 1)
		return 1;
	else if (i == 2)
		return 2;
	return 0;
}

int 		main(int ac, char **av)
{
	Gomoku* gomoku;

	if (ac > 1)
	{
		gomoku = parsingParameters(ac, av);
	}
	else
	{
		gomoku = new Gomoku();
	}

	if (gomoku->getGameMode() == -1)
		gomoku->setGameMode( selectGameMode( ) );

	displayInformation(gomoku);

	CoreEngine *engine = new CoreEngine(50);
	engine->setGame(gomoku);
	engine->start();

	return (0);
}