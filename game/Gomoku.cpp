#include "Gomoku.hpp"
#include "../engine/CoreEngine.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <time.h>

Gomoku::Gomoku( void )
{
	this->_currentBoard = new Board();
	this->_lastClick = new double[3];
	this->_lastClick[0] = 0;
	this->_lastClick[1] = 0;
	this->_lastClick[2] = 0;
	this->_firstPlayerTurn = true;
	this->_verbose = false;
	this->_assist = false;
	this->_gameMode = 0;
	this->_currentBoard->_assist = std::make_pair(-1, -1);
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
			if (getAssist())
				this->_player1->_assistant = new Computer(1);
		}
		else
		{
			this->_player1 = new Player(1, 0x000000);
			this->_player2 = new Player(2, 0xFFFFFF);
			_player1->setOpponent(_player2);
			_player2->setOpponent(_player1);
			if (getAssist())
			{
				this->_player1->_assistant = new Computer(1);
				this->_player2->_assistant = new Computer(2);
			}
		}

		srand(time(NULL)); // initialisation de rand
		int nombre_aleatoire = 0;
		nombre_aleatoire = rand() % 2;
		if (nombre_aleatoire)
			this->_firstPlayerTurn = false;
}

void			Gomoku::Swap1Player(Player *player, int stepTo)
{
	std::pair<int, int> ret;
	static int step = 0;
	std::cout << "Starting swap1 Mod step:" << step << std::endl;
	if (isClicked())
	{
		while (player->referee(_currentBoard, getPair()) == true) // while ? 
		{
			ret = player->play(_currentBoard, getPair());
			_currentBoard->insert(ret, player);
			capturePawns(_currentBoard->checkCapture(ret.first, ret.second), player);
			_currentBoard->stockAlignement(ret);
			endTurn();
			step++;
			if (step == stepTo)
				this->setGameMode(0);
		}
	}

}

void			Gomoku::Swap1Computer(Player *player, int stepTo)
{
	static int step = 0;

	std::pair<int, int> ret;

	if (step == 0) 
		ret = std::make_pair( 9, 9 );//computer
	if (step == 1) 
		ret = std::make_pair( 10, 9 );//player
	if (step == 2) 
		ret = std::make_pair( 10, 10 );//computer
	if (step == 3) 
		ret = std::make_pair( 10, 11 );//player
	if (step == 4) 
		ret = std::make_pair( 11, 11 );//computer
	
	_currentBoard->insert(ret, player);
	capturePawns(_currentBoard->checkCapture(ret.first, ret.second), player);
	_currentBoard->stockAlignement(ret);
	endTurn();
	step++;

	if (step == stepTo)
		this->setGameMode(0);
}

void			Gomoku::playerTurn(Player *player)
{
	std::pair<int, int> ret;
	Possibility*		ret2;

	Computer* check = dynamic_cast<Computer*>(player);

	static int firstTurn = 0; // 1 for player 2 for computer
	if (this->_gameMode == 1)
	{
		if (firstTurn == 0)
			firstTurn = (!check) ? 1 : 2;

		if (firstTurn == 1)
			Swap1Player(player, 2);
		else
			Swap1Computer(player, 2);

	}
	else if (this->_gameMode == 2)
	{
		if (firstTurn == 0)
			firstTurn = (!check) ? 1 : 2;

		if (firstTurn == 1)
			Swap1Player(player, 4);
		else
			Swap1Computer(player, 4);
	}	
	else if (!check)
	{
		if (getAssist())
		{
			ret2 = player->_assistant->play(_currentBoard);
			_currentBoard->_assist = std::make_pair(ret2->getX(), ret2->getY());
		}
		if (isClicked())
		{
			_currentBoard->_assist = std::make_pair(-1, -1);
			while (player->referee(_currentBoard, getPair()) == true) // while ? 
			{
				ret = player->play(_currentBoard, getPair());
				_currentBoard->insert(ret, player);
				capturePawns(_currentBoard->checkCapture(ret.first, ret.second), player);
				_currentBoard->stockAlignement(ret);
				endTurn();
			}
		}
	}
	else if (check)
	{
		const clock_t begin_time = clock();

		ret2 = check->play(_currentBoard);

  		std::cout<<"Took " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s to place pawn. "<< std::endl;

		ret = std::make_pair(ret2->getX(), ret2->getY());
		capturePawns(ret2->_capturedPawns, player);
		_currentBoard->insert(ret, player);
		_currentBoard->stockAlignement(ret);
		endTurn();
	}
}

void				Gomoku::play()
{
	if (this->_currentBoard->checkwin(_player1, _player2))
	{
		// this->endGame();
		this->_currentBoard->setGameEnded();
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

void				Gomoku::setVerbose(bool isDebugMode)
{
	this->_verbose = isDebugMode;
}

bool				Gomoku::getVerbose( void ) const
{
	return this->_verbose;
}

void				Gomoku::setAssist(bool isAssist)
{
	this->_assist = isAssist;
}

bool				Gomoku::getAssist( void ) const
{
	return this->_assist;
}

void				Gomoku::setGameMode(int gameMode)
{
	this->_gameMode = gameMode;
}

int				Gomoku::getGameMode( void ) const
{
	return this->_gameMode;
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
	for (int i = 0 ; i < _player1->_capturedPawns; i++)
	{
		_renderLib->drawCircle(-1, 1 + i, 1, _player2->getColor());
	}
	for (int i = 0 ; i < _player2->_capturedPawns; i++)
	{
		_renderLib->drawCircle(19, 1 + i, 1, _player1->getColor());
	}
	return true;
}



