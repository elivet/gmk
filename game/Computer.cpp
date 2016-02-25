#include "Computer.hpp"
#include <stdlib.h>

Computer::Computer( void )
{
	this->_name = 2;
	this->_capturedPawns = 0;
	this->_color = 0xFFFFFF;
	return ;
}

Computer::Computer( int name )
{
	this->_name = name;
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

Possibility*			Computer::play(Board* currentBoard)
{
	std::pair<int, int> key; // = std::make_pair(1,2);
	Possibility* max;

	_currentBoard = currentBoard;
	if (_currentBoard->getPawns().size() == 0)
	{
		max = new Possibility(9, 9, this->getName());
	}
	else
	{
		getSons(false);
		max = getSonsMax();
		key = std::make_pair(max->getX(), max->getY());
		_sonsDisplay = _sons;
		_sons.clear();
	}
	return max;
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
		if (_sons[i]->getWeight() >= ret->getWeight())
		{
			ret = _sons[i];
		}
	}

	if (!this->referee(_currentBoard, std::make_pair(ret->getX(), ret->getY())))
    {
		for (std::vector<Possibility*>::iterator it = _sons.begin(); it != _sons.end(); /*it++*/)
		{
			if (*it == ret) 
				it = _sons.erase(it);
			else 
	      		++it;
	 	}
        getSonsMax();
    }
	return ret;
}

int 					Computer::getGrandSonsMin(Possibility* son)
{
	int weight = son->getGrandSons().begin()->second->getWeight();

	for (std::map<std::pair<int,int>, Possibility*>::iterator it=son->_grandSons.begin() ; it!=son->_grandSons.end() ; ++it)
	{
		if (it->second->getWeight() <= weight && it->second->getWeight() > -2147483648)
		{
			weight = it->second->getWeight();	
		}
	}
	return weight;
}

void					Computer::createSon(int x, int y)
{
	if (x >= 0 && x < 19 && y >= 0 && y < 19)
	{
		_tmp = new Possibility(x, y, this->_name);
		_currentBoard->insert(std::make_pair(x, y), this);
		_currentBoard->stockAlignement(std::make_pair(x, y));
		this->_tmp->_capturedPawns = _currentBoard->checkCapture(_tmp->getX(), _tmp->getY()); // nbr de pions captures
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


int 			Computer::riskCapture(Alignement* alignement)
{
	int ret = 0;
	Pawn *tmp;
	tmp = _currentBoard->findPawn(alignement->getPawnEnd()->getX() + alignement->getNx(), alignement->getPawnEnd()->getY() + alignement->getNy());
	if (tmp && tmp->getPlayer()->getName() != alignement->getPawnBegin()->getPlayer()->getName())
		ret++;
	tmp = _currentBoard->findPawn(alignement->getPawnBegin()->getX() + alignement->getPx(), alignement->getPawnBegin()->getY() + alignement->getPy());
	if (tmp && tmp->getPlayer()->getName() != alignement->getPawnBegin()->getPlayer()->getName())
		ret++;
	return ret;

}



int			Computer::countAlignements(int x, int y)
{
	int weight = 0;
	Pawn *currentPawn = _currentBoard->findPawn(x, y);
	int 	alignementSize = 0;
	int 	alignementPlayer;

	

	currentPawn = _currentBoard->findPawn(_tmp->getX(), _tmp->getY());

	for (unsigned int i = 0; i < _currentBoard->_alignements.size(); i++)
	{
		alignementSize = _currentBoard->_alignements[i]->getNbr();
		alignementPlayer = _currentBoard->_alignements[i]->getPawnBegin()->getPlayer()->getName();
		if (alignementSize == 5)
		{
			if (alignementPlayer == getName())
			{
				weight += 150000;
			}
			else if (alignementPlayer != getName())
			{
				weight -= 550000;
			}
		}
		else if (alignementSize == 4)
		{
			if (alignementPlayer == getName())
			{
				weight += 10000;
				if (riskCapture(_currentBoard->_alignements[i]) == 2)
					weight -= 10000;				
			}
			else if (alignementPlayer != getName())
			{
				weight -= 50000;
				weight += 10000 * riskCapture(_currentBoard->_alignements[i]);
			}
		}
		else if (alignementSize == 3)
		{
			if (alignementPlayer == getName())
			{
				weight += 1000;
				if (riskCapture(_currentBoard->_alignements[i]) == 2)
					weight -= 10000;
			}
			else if (alignementPlayer != getName())
			{
				weight -= 5000;	
				weight += 10000 * riskCapture(_currentBoard->_alignements[i]);
			}
		}
		else if (alignementSize == 2)
		{
			if (alignementPlayer == getName())
			{
				weight += 10;
				weight -= 10000 * riskCapture(_currentBoard->_alignements[i]);
			}
			else if (alignementPlayer != getName())
			{
				weight -= 50;
				weight += 10000 * riskCapture(_currentBoard->_alignements[i]);
			}
		}
	}
	return weight;
}



void			Computer::setWeight(int x, int y)
{
	int weight = 1;
	_currentBoard->insert(std::make_pair(x, y), this);

	this->_tmp->getGrandSons()[std::make_pair(x, y)]->_capturedPawns = _currentBoard->checkCapture(x, y); // nbr de pions captures par le petit fils
	weight -=  (this->_tmp->_capturedPawns.size() - this->_tmp->getGrandSons()[std::make_pair(x, y)]->_capturedPawns.size()) * 25000;
	weight += this->_tmp->_capturedPawns.size() * 50000;


	weight += countAlignements(x, y);


	this->_tmp->getGrandSons()[std::make_pair(x, y)]->setWeight(weight);
	_currentBoard->erase(std::make_pair(x, y));

	return ;
}













