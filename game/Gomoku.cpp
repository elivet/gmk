#include "Gomoku.hpp"
#include "../engine/CoreEngine.hpp"
#include <stdlib.h>
#include <stdio.h>

Gomoku::Gomoku( void )
{
	this->_currentBoard = new Board();
	this->_lastClick = new double[3];
	this->_lastClick[0] = 0;
	this->_lastClick[1] = 0;
	this->_lastClick[2] = 0;
	this->_firstPlayerTurn = true;
	return ;
}

Gomoku::~Gomoku( void )
{
	return ;
}

Gomoku::Gomoku( Gomoku const & src ):GameObject()
{
	*this = src;
}

Gomoku &	Gomoku::operator=( Gomoku const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

/****************************************************************
***************************GAME**********************************
*****************************************************************/

void				Gomoku::init( void )
{
		bool comp = false;
		std::string	c;
		while (c != "y" && c != "n")
		{
			std::cout << "Do you wanna play against the computer ? (y/n)" << std::endl;
			std::cin >> c;
			if (c == "y")
				comp = true;
			else if (c == "n")
				comp = false;
			else
				std::cout << "Please answer yes or no (y/n)" << std::endl;
		}

		if ( comp )
		{
			this->_player1 = new Player();
			this->_player2 = new Computer();
			_player1->setOpponent(_player2);
			_player2->setOpponent(_player1);
		}
		else
		{
			this->_player1 = new Player(1, 0x000000);
			this->_player2 = new Player(2, 0xFFFFFF);
			_player1->setOpponent(_player2);
			_player2->setOpponent(_player1);
		}

		srand(time(NULL)); // initialisation de rand
		int nombre_aleatoire = 0;
		nombre_aleatoire = rand() % 2;
		if (nombre_aleatoire)
			this->_firstPlayerTurn = false;
}

void			Gomoku::playerTurn(Player *player)
{
	std::pair<int, int> ret;
	Possibility*		ret2;

	Computer* check = dynamic_cast<Computer*>(player);
	if (!check && isClicked())
	{
		while (player->referee(_currentBoard, getPair()) == true) // while ? 
		{
			std::cout << "Gomoku::playerTurn 1" << std::endl;	
			ret = player->play(_currentBoard, getPair());
			std::cout << "Gomoku::playerTurn 2" << std::endl;	
			_currentBoard->insert(ret, player);
			std::cout << "Gomoku::playerTurn 3" << std::endl;	
			capturePawns(_currentBoard->checkCapture(ret.first, ret.second), player);
			std::cout << "Gomoku::playerTurn 4" << std::endl;	
			_currentBoard->stockAlignement(ret);
			std::cout << "Gomoku::playerTurn 5" << std::endl;	
			endTurn();
		}
	}
	else if (check)
	{
			std::cout << "Gomoku::playerTurn 6" << std::endl;	
		ret2 = check->play(_currentBoard);
			std::cout << "Gomoku::playerTurn 7" << std::endl;	
		ret = std::make_pair(ret2->getX(), ret2->getY());
			std::cout << "Gomoku::playerTurn 8" << std::endl;	
		capturePawns(ret2->_capturedPawns, player);
			std::cout << "Gomoku::playerTurn 9" << std::endl;	
		//referee
		_currentBoard->insert(ret, player);
			std::cout << "Gomoku::playerTurn 10" << std::endl;	
		_currentBoard->stockAlignement(ret);
			std::cout << "Gomoku::playerTurn 11" << std::endl;	
		endTurn();
	}
}

void				Gomoku::play()
{
	if (this->_currentBoard->checkwin(_player1, _player2))
	{
		// this->endGame();
		return ;
	}
	if (this->_firstPlayerTurn)
	{	
		playerTurn(_player1);
	}
	else
	{
		playerTurn(_player2);
	}
	return ;
}

void				Gomoku::capturePawns(std::vector<std::pair<int, int> >  capturedPawns, Player* player)
{
	for (unsigned int i = 0; i < capturedPawns.size(); i++)
	{
		_currentBoard->erase(capturedPawns[i]);
		player->_capturedPawns++;
	}
	return ; 
}

void				Gomoku::endGame( void )
{
	this->getCoreEngine()->setRunnig(false);
}


std::pair<int, int>	Gomoku::getPair( void )
{
	int x = this->_lastClick[0];
	int y = this->_lastClick[1];
	return std::make_pair( x, y );
}

bool				Gomoku::isClicked( void )
{
	return (this->_lastClick[2]);
}

void				Gomoku::endTurn( void )
{
	this->_lastClick[2] = 0;
	this->_firstPlayerTurn = !this->_firstPlayerTurn;

}

/****************************************************************
***************************ENGINE********************************
*****************************************************************/

void				Gomoku::setCoreEngine(CoreEngine * coreEngine)
{
	_coreEngine = coreEngine;
}

CoreEngine*			Gomoku::getCoreEngine( void ) const
{
	return ( this->_coreEngine );
}

int					Gomoku::update( OpenGlLib *	_renderLib, double delta )
{
	(void)_renderLib;
	(void)delta;
	// std::cout << "Gomoku::update1" << std::endl;
	this->_lastClick = &(_renderLib->OpenGlLib::lastClick[0]);
	// std::cout << "Gomoku::update2" << std::endl;
	this->play();
	// std::cout << "Gomoku::update3" << std::endl;

	return true;
}

int					Gomoku::render( OpenGlLib *	_renderLib ) const
{
	// std::cout << "Gomoku::render1" << std::endl;
	_currentBoard->render(_renderLib);
	// std::cout << "Gomoku::render2" << std::endl;

	// if (_renderLib->isMouseClicked())
	// {
	// 	int x = (int)_renderLib->OpenGlLib::lastClick[0];
	// 	int y = (int)_renderLib->OpenGlLib::lastClick[1];
	// 	_currentBoard->insert(std::make_pair(x, y), 1);
	// 	_renderLib->OpenGlLib::lastClick[2] = 0.0;
	// }
	return true;
}



