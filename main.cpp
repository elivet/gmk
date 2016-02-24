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
	while ( (opt = getopt(ac, av, "dhl")) != -1 ) 
	{
		switch ( opt ) 
		{
			case 'd':
				gomoku->setVerbose(true);
			break;
			case 'l':
				gomoku->setAssist(true);
			break;   
			case 'h':
				std::cout << "Gomoku is an awesome, where you lose alsmost every time, just launch it and pres y and enter to play against the computer" << std::endl;
				std::cout << "-h : to display debug to understand how the IA algorithm works" << std::endl;
				std::cout << "-l : to get help if you don't know how to play" << std::endl;
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

	displayInformation(gomoku);

	CoreEngine *engine = new CoreEngine(50);
	engine->setGame(gomoku);
	engine->start();

	return (0);
}