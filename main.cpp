#include <utility>
#include <iostream> 
#include <string> 
#include <map>
#include "game/Board.hpp"
#include "engine/OpenGlLib.hpp"
#include <unistd.h>


int 		main()
{
	std::cout << "wefwef" << std::endl;
	OpenGlLib *lib = new OpenGlLib();
	lib->createWindow(50, 50 , "efwef");

	return (0);
}