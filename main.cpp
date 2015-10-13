#include <utility>
#include <iostream> 
#include <string> 
#include <map>
#include "engine/OpenGlLib.hpp"

int 		main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	OpenGlLib *blop = new OpenGlLib();
	blop->createWindow(100, 100, "oooh yeah");
	return (0);
}