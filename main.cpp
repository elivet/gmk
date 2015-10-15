#include <utility>
#include <iostream> 
#include <string> 
#include <map>
#include "game/Board.hpp"
#include "engine/CoreEngine.hpp"
#include <unistd.h>


int 		main()
{
	std::cout << "wefwef" << std::endl;
	CoreEngine *engine = new CoreEngine(50);
	engine->start();

	return (0);
}