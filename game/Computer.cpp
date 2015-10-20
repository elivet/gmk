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

	_currentBoard = currentBoard;
	if (_currentBoard->getPawns().size() == 0)
		_currentBoard->insert(std::make_pair(1,2), 1);
	else
	{
		std::cout << "getSons" << std::endl; 
		getSons(false);
		displaySons();
		exit(0);
	}

	return key;
}

void						Computer::getSons(bool bill)
{
	int loop = 0;
	std::map<std::pair<int,int>, Pawn*>		pawns = _currentBoard->getPawns();
	for(std::map<std::pair<int,int>, Pawn*>::iterator it=pawns.begin() ; it!=pawns.end() ; it++)
	{
		loop++;
		std::cout << "beginLOOP getSons loop: " << loop << " size: " << _currentBoard->getPawns().size() << std::endl;
		int x = it->first.first;
		int y = it->first.second;
		lookAround(x, y, bill);
		std::cout << "endLOOP getSons" << std::endl;
	}
	
	// std::cout << "displaySons getSons" << std::endl;
	// displaySons();
	return ;
}

void					Computer::lookAround(int x, int y, bool bill)
{
	emptyAround(x - 1, y, bill);
	emptyAround(x - 1, y - 1, bill);
	emptyAround(x + 1, y, bill);
	emptyAround(x + 1, y + 1, bill);
	emptyAround(x, y - 1, bill);
	emptyAround(x, y + 1, bill);
	emptyAround(x + 1, y - 1, bill);
	emptyAround(x - 1, y + 1, bill);
}

void					Computer::emptyAround(int x, int y, bool bill)
{
	std::cout << " @@@@@@@@@@@@@@       Around x: " << x << " y: " << y << std::endl;
	if (!_currentBoard->findPawn(x, y))
	{
		if (!bill)
			createSon(x, y);
		else
			createGrandSon(x, y);
	}
	return ;
}

void					Computer::createGrandSon(int x, int y)
{
	if (x >= 0 && x < 19 && y >= 0 && y < 19)
	{
		std::cout << "createGrandSon0 x: " << x << " y: " << y << std::endl;
		this->_tmp->insert(x, y, _name);
		std::cout << "createGrandSon SIZE: " << this->_tmp->getGrandSons().size() << std::endl;
	}
	return ;
}

void					Computer::createSon(int x, int y)
{
	if (x >= 0 && x < 19 && y >= 0 && y < 19)
	{
		std::cout << "createSon0 x: " << x << " y: " << y << std::endl;
		_tmp = new Possibility(x, y, this->_name);
		_currentBoard->insert(std::make_pair(x, y), this->_name);
		getSons(true);
		_currentBoard->erase(std::make_pair(x, y));
		if (_currentBoard->findPawn(x, y) == NULL)
			std::cout << "PAWN ERASED MUTAFUCKA" << std::endl;
		else
			std::cout << "PAWN NOT NOT NOT ERASED MUTAFUCKA" << std::endl;
		this->_sons.push_back(_tmp);
		std::cout << "createSon SIZE: " << _sons.size() << std::endl;
	}
	return ;
}

void					Computer::displaySons()
{
	std::cout << "displaySons SIZE: " << _sons.size() << std::endl;
	for (unsigned int i = 0; i < _sons.size(); i++)
	{
		std::cout << "SON x: " << _sons[i]->getX() << " y: " << _sons[i]->getY() << std::endl;
		for(std::map<std::pair<int,int>, Possibility*>::iterator it=_sons[i]->_grandSons.begin() ; it!=_sons[i]->_grandSons.end() ; ++it)
		{
			std::cout << "GRANDSON x: " << it->first.first << " GRANDSON y: " << it->first.second << std::endl;
		}
	}
	return ;
}













