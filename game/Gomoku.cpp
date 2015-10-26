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
		}
		else
		{
			this->_player1 = new Player(1, 0x000000);
			this->_player2 = new Player(2, 0xFFFFFF);
		}

		srand(time(NULL)); // initialisation de rand
		int nombre_aleatoire = 0;
		nombre_aleatoire = rand() % 2;
		if (nombre_aleatoire)
			this->_firstPlayerTurn = false;
}

void				Gomoku::play()
{
	std::pair<int, int> ret;
	if (this->_currentBoard->checkwin())
	{
		this->endGame();
		return ;
	}
	if (this->_firstPlayerTurn)
	{	
		Computer* check = dynamic_cast<Computer*>(_player1);
		if (!check && isClicked())
		{
			ret = _player1->play(_currentBoard, getPair());
			_currentBoard->insert(ret, _player1);
			_currentBoard->stockAlignement(ret);
			endTurn();
		}
		else if (check)
		{
			ret = check->play(_currentBoard);
			_currentBoard->insert(ret, _player1);
			_currentBoard->stockAlignement(ret);
			endTurn();
		}
	}
	else
	{
		Computer* check2 = dynamic_cast<Computer*>(_player2);
		if (!check2 && isClicked())
		{
			ret = _player2->play(_currentBoard, getPair());
			_currentBoard->insert(ret, _player2);
			_currentBoard->stockAlignement(ret);
			endTurn();
		}
		else if (check2)
		{
			ret = check2->play(_currentBoard);
			_currentBoard->insert(ret, _player2);
			_currentBoard->stockAlignement(ret);
			endTurn();
		}
	}
	return ;
}

// void				Gomoku::turns(Player* p1, Player* p2)
// {
// 	std::pair<int, int> tmp;
// 	while (!this->_currentBoard->checkwin())
// 	{
// 		tmp = p1->play(this->_currentBoard);
// 		// _currentBoard->insert(tmp, p1->getName());
// 		tmp = p2->play(this->_currentBoard);
// 		// _currentBoard->insert(tmp, p2->getName());
// 	}
// 	return ;
// }

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
	this->_lastClick = &(_renderLib->OpenGlLib::lastClick[0]);
	this->play();

	return true;
}

int					Gomoku::render( OpenGlLib *	_renderLib ) const
{
	_currentBoard->render(_renderLib);

	// if (_renderLib->isMouseClicked())
	// {
	// 	int x = (int)_renderLib->OpenGlLib::lastClick[0];
	// 	int y = (int)_renderLib->OpenGlLib::lastClick[1];
	// 	_currentBoard->insert(std::make_pair(x, y), 1);
	// 	_renderLib->OpenGlLib::lastClick[2] = 0.0;
	// }
	


	return true;
}



