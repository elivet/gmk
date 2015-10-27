#include "Computer.hpp"
#include <stdlib.h>

Computer::Computer( void )
{
	this->_name = 2;
	this->_capturedPawns = 0;
	this->_color = 0xFFFFFF;
	return ;
}


Computer::~Computer( void )
{
	return ;
}

Computer::Computer( Computer const & src ):Player()
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
	std::pair<int, int> key; // = std::make_pair(1,2);

	_currentBoard = currentBoard;
	if (_currentBoard->getPawns().size() == 0)
	{
		key = std::make_pair(9,9);
	}
	else
	{
		getSons(false);
		Possibility* max = getSonsMax();
		std::cout << "Computer play x: " << max->getX() << " y: " << max->getY() << std::endl;
		key = std::make_pair(max->getX(), max->getY());
		_sons.clear();
		// displaySons();
		// exit(0);
	}

	return key;
}

void						Computer::getSons(bool bill)
{
	std::map<std::pair<int,int>, Pawn*>		pawns = _currentBoard->getPawns();
	for(std::map<std::pair<int,int>, Pawn*>::iterator it=pawns.begin() ; it!=pawns.end() ; it++)
	{
		int x = it->first.first;
		int y = it->first.second;
		lookAround(x, y, bill);
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
		this->_tmp->insert(x, y, _name);
		this->setWeight(x, y);
	}
	return ;
}

Possibility* 					Computer::getSonsMax() // 
{
	Possibility* ret = new Possibility();

	for (unsigned int i = 0; i < _sons.size(); i++)
	{
		if (_sons[i]->getWeight() > ret->getWeight())
			ret = _sons[i];
	}
	return ret;
}

int 					Computer::getGrandSonsMin(Possibility* son)
{
	int weight = son->getGrandSons().begin()->second->getWeight();

	for (std::map<std::pair<int,int>, Possibility*>::iterator it=son->_grandSons.begin() ; it!=son->_grandSons.end() ; ++it)
	{
		if (it->second->getWeight() < weight)
			weight = it->second->getWeight();
	}
	return weight;
}

void					Computer::createSon(int x, int y)
{
	if (x >= 0 && x < 19 && y >= 0 && y < 19)
	{
		_tmp = new Possibility(x, y, this->_name);
		_currentBoard->insert(std::make_pair(x, y), this);
		getSons(true);
		_tmp->setWeight(getGrandSonsMin(_tmp));
		_currentBoard->erase(std::make_pair(x, y));
		this->_sons.push_back(_tmp);
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

bool 					Computer::spaceDisp(Alignement* alignement, int nbr)
{
	int count = 1;
	nbr = 5 - nbr;

	std::pair<int, int> currentKey = std::make_pair(alignement->getPawnEnd()->getX() + alignement->getNx(), alignement->getPawnEnd()->getY() + alignement->getNy());
	while (!_currentBoard->findPawn(currentKey.first, currentKey.second) && currentKey.first >= 0 && currentKey.first < 19 && currentKey.second >= 0 && currentKey.second < 19)
	{
		currentKey = std::make_pair(currentKey.first + alignement->getNx(), currentKey.second + alignement->getNy());
		count++;
	}
	currentKey = std::make_pair(alignement->getPawnBegin()->getX() + alignement->getPx(), alignement->getPawnBegin()->getY() + alignement->getPy());
	while (!_currentBoard->findPawn(currentKey.first, currentKey.second) && currentKey.first >= 0 && currentKey.first < 19 && currentKey.second >= 0 && currentKey.second < 19)
	{
		currentKey = std::make_pair(currentKey.first + alignement->getPx(), currentKey.second + alignement->getPy());
		count++;
	}
	if (count >= nbr)
		return true;
	return false;
}

bool 					Computer::inAlignementWay(Alignement* alignement, Pawn* currentPawn)
{
	if (alignement->getPawnEnd()->getX() + alignement->getNx() == currentPawn->getX() && alignement->getPawnEnd()->getY() + alignement->getNy() == currentPawn->getY())
		return true;
	if (alignement->getPawnBegin()->getX() + alignement->getPx() == currentPawn->getX() && alignement->getPawnBegin()->getY() + alignement->getPy() == currentPawn->getY())
		return true;
	return false;
}

int 					Computer::spyOpponent(int x, int y, Pawn* currentPawn)
{
	int 	weight = 0;
	Pawn*	neighbourg = _currentBoard->findPawn(x, y);

	if (neighbourg && neighbourg->getPlayer()->getName() != currentPawn->getPlayer()->getName())
	{
		for (unsigned int i = 0; i < neighbourg->_alignements.size(); i++)
		{
			std::cout << "spyOpponent alignementloop" << std::endl;
			if (inAlignementWay(neighbourg->_alignements[i], currentPawn) && spaceDisp(neighbourg->_alignements[i], neighbourg->_alignements[i]->getNbr()))
			{
				weight = neighbourg->_alignements[i]->getNbr() * 100 - 50;
				return weight;
			}
		}
	}
	return weight;
}

int 					Computer::spyAround(int x, int y)
{
	int weight = 0;
	Pawn*	current = _currentBoard->findPawn(x, y);

	if (current)
	{
		spyOpponent(x - 1, y, current);
		spyOpponent(x - 1, y - 1, current);
		spyOpponent(x + 1, y, current);
		spyOpponent(x + 1, y + 1, current);
		spyOpponent(x, y - 1, current);
		spyOpponent(x, y + 1, current);
		spyOpponent(x + 1, y - 1, current);
		spyOpponent(x - 1, y + 1, current);
	}
	
	return weight;
}

int 					Computer::observeOwn(int x, int y, Pawn* currentPawn)
{
	int 	weight = 0;
	Pawn*	neighbourg = _currentBoard->findPawn(x, y);

	if (neighbourg && neighbourg->getPlayer()->getName() == currentPawn->getPlayer()->getName())
	{
		for (unsigned int i = 0; i < neighbourg->_alignements.size(); i++)
		{
			std::cout << "observeOwn alignementloop" << std::endl;
			if (inAlignementWay(neighbourg->_alignements[i], currentPawn) && spaceDisp(neighbourg->_alignements[i], neighbourg->_alignements[i]->getNbr()))
			{
				weight = neighbourg->_alignements[i]->getNbr() * 100;
				return weight;
			}
		}
	}
	return weight;
}

int 					Computer::observeAround(int x, int y)
{
	int weight = 0;
	Pawn*	current = _currentBoard->findPawn(x, y);

	if (current)
	{
		observeOwn(x - 1, y, current);
		observeOwn(x - 1, y - 1, current);
		observeOwn(x + 1, y, current);
		observeOwn(x + 1, y + 1, current);
		observeOwn(x, y - 1, current);
		observeOwn(x, y + 1, current);
		observeOwn(x + 1, y - 1, current);
		observeOwn(x - 1, y + 1, current);
	}
	
	return weight;
}
void			Computer::setWeight(int x, int y)
{
	int weight = 1;
	_currentBoard->insert(std::make_pair(x, y), this);
	if (_currentBoard->checkwin())
	{
		if (_currentBoard->getWin() == this->_name)
			weight += 1000;
		else
			weight -= 1000;
	}

	this->_tmp->getGrandSons()[std::make_pair(x, y)]->_capturedPawns = _currentBoard->checkCapture(x, y); // nbr de pions captures
	weight += this->_tmp->getGrandSons()[std::make_pair(x, y)]->_capturedPawns.size(); // * 10 a revoir

	weight += spyAround(x, y);
	weight += observeAround(x, y);

	std::cout << "WEIGHT: " << weight << std::endl;
	this->_tmp->getGrandSons()[std::make_pair(x, y)]->setWeight(weight);
	_currentBoard->erase(std::make_pair(x, y));

	return ;
}













