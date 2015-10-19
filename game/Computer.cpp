#include "Computer.hpp"

Computer::Computer( void )
{
	this->_name = 2;
	this->_capturedPawns = 0;
	return ;
}


Computer::~Computer( void )
{
	return ;
}

Computer::Computer( Computer const & src )
{
	*this = src;
}

Computer &	Computer::operator=( Computer const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

std::pair<int, int>			Computer::play(Board* currentBoard)
{
	std::cout << "Computer playing" << std::endl;
	std::pair<int, int> key = std::make_pair(1, 3);

	if (currentBoard->getPawns().size() == 0)
		currentBoard->insert(std::make_pair(1,2), 1);
	else
	{
		std::cout << "getSons" << std::endl; 
		getSons(currentBoard);
	}
	return key;
}

void						Computer::getSons(Board* currentBoard)
{
	for(std::map<std::pair<int,int>, Pawn*>::iterator it=currentBoard->getPawns().begin() ; it!=currentBoard->getPawns().end() ; ++it)
	{
		std::cout << "beginLOOP getSons" << std::endl;
		int x = it->first.first;
		int y = it->first.second;
		emptyAround(currentBoard, x - 1, y);
		emptyAround(currentBoard, x - 1, y - 1);
		emptyAround(currentBoard, x + 1, y);
		emptyAround(currentBoard, x + 1, y + 1);
		emptyAround(currentBoard, x, y - 1);
		emptyAround(currentBoard, x, y + 1);
		emptyAround(currentBoard, x + 1, y - 1);
		emptyAround(currentBoard, x - 1, y + 1);
		std::cout << "endLOOP getSons" << std::endl;
	}
	std::cout << "displaySons getSons" << std::endl;
	displaySons();
	return ;
}

void					Computer::emptyAround(Board* currentBoard, int x, int y)
{
	// std::cout << " @@@@@@@@@@@@@@       Around x: " << x << " y: " << y << std::endl;
	// if (!currentBoard->findPawn(x, y))
	// {
	// 	createSon(currentBoard, x, y);
	// }

	(void)currentBoard;
	(void)x;
	(void)y;
	return ;
}


// void					Computer::createSon(Board* currentBoard, int x, int y)
// {
// 		std::cout << "createSon0 x: " << x << " y: " << y << std::endl;
// 	if (x >= 0 && x < 19 && y >= 0 && y < 19)
// 	{
// 		std::cout << "createSon1" << std::endl;
// 		Board* son = new Board(*currentBoard);
// 		std::cout << "createSon2" << std::endl;
// 		son->insert(std::make_pair(x, y), this->_name);
// 		std::cout << "createSon3" << std::endl;
// 		son->displayPawns();
// 		std::cout << "createSon4" << std::endl;
// 		_sons.push_back(son);
// 		std::cout << "createSon5" << std::endl;
// 	}
// 		std::cout << "createSon6" << std::endl;
// 	return ;
// }

void					Computer::displaySons()
{
	for (unsigned int i = 0; i < _sons.size(); i++)
	{
		_sons[i]->displayPawns();
	}
	return ;
}













