#include <utility>
#include <iostream> 
#include <string> 
#include <map>
#include "game/Board.hpp"
#include "engine/OpenGlLib.hpp"

int 		main()
{
	OpenGlLib *blop = new OpenGlLib();
	blop->createWindow(100, 100, "oooh yeah");
	return (0);
}