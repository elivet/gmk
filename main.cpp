#include <utility>
#include <iostream> 
#include <string> 
#include <map>
#include <stdio.h>
#include <string.h>
#include "game/Board.hpp"
#include "./game/Gomoku.hpp"
//#include "engine/OpenGlLib.hpp"
// #include "engine/CoreEngine.hpp"
#include <unistd.h>


int 		main()
{
	Gomoku* gomoku;
	std::string	c;

	while (c != "y" && c != "n")
	{
		std::cout << "Do you wanna play against the computer ? (y/n)" << std::endl;
		std::cin >> c;
		if (c == "y")
			gomoku = new Gomoku(true);
		else if (c == "n")
			gomoku = new Gomoku(false);
		else
			std::cout << "Please answer yes or no (y/n)" << std::endl;
	}
	gomoku->play();
	std::cout << "wefwef" << std::endl;
	// CoreEngine *engine = new CoreEngine(50);
	// engine->start();

	return (0);
}