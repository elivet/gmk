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


int 		main()
{
	Gomoku* gomoku = new Gomoku();

	
	CoreEngine *engine = new CoreEngine(50);
	engine->setGame(gomoku);
	engine->start();

	// gomoku->play();



	return (0);
}