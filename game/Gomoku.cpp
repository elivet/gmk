#include "Gomoku.hpp"

Gomoku::Gomoku( void )
{
	return ;
}

Gomoku::Gomoku( bool comp )
{
	this->_currentBoard = new Board();

	if ( comp )
	{
		this->_player1 = new Player();
		this->_player2 = new Computer();
	}
	else
	{
		this->_player1 = new Player(1);
		this->_player2 = new Player(2);
	}
	return ;
}

Gomoku::~Gomoku( void )
{
	return ;
}

Gomoku::Gomoku( Gomoku const & src )
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

void		Gomoku::play()
{
	// _currentBoard->insert(std::make_pair(1,2), 1);
	// _currentBoard->insert(std::make_pair(2,3), 1);
	// _currentBoard->insert(std::make_pair(3,4), 1);
	// _currentBoard->insert(std::make_pair(4,5), 1);
	// _currentBoard->insert(std::make_pair(5,6), 1);




	srand(time(NULL)); // initialisation de rand
	int nombre_aleatoire = 0;
	nombre_aleatoire = rand() % 2;
	if (nombre_aleatoire)
		this->turns(_player1, _player2);
	else
		this->turns(_player2, _player1);
	return ;
}

void		Gomoku::turns(Player* p1, Player* p2)
{
	std::pair<int, int> tmp;
	while (!this->_currentBoard->checkwin())
	{
		tmp = p1->play(this->_currentBoard);
		// _currentBoard->insert(tmp, p1->getName());
		tmp = p2->play(this->_currentBoard);
		// _currentBoard->insert(tmp, p2->getName());
	}
	return ;
}

int					Gomoku::update( OpenGlLib *	_renderLib, double delta )
{
	(void)_renderLib;
	(void)delta;
	return true;
}

int					Gomoku::render( OpenGlLib *	_renderLib ) const
{
	int color = 0x000000;
	int color2 = 0xFFFFFF;
	// for (int i = 0; i < 1; i++)
	// {
	// 	for (int j = 0; j < 19; j++)
	// 	{
	// 		color += 0x000F0F;
	// 		_renderLib->drawSquare(j, i , 1, color);
	// 	}
	// }
	for (int j = 0; j < 20; j++)
	{
		for(int i =0; i < 20; i++)
		{
			color += 0x000F0F;
			color2 += 0xFF0000;
			_renderLib->drawSquare(i, j, 1, color);
			_renderLib->drawCircle(i, j, 1, color2);
		}
	}
	// _renderLib->drawLine(1, 0, 1, 20, 0xFF0000);
	// _renderLib->drawLine(0, 0, 1, 10, 0xFF0000);


	// _renderLib->drawSquare(0, 1 , 1, 0xFF0000);
	// _renderLib->drawSquare(2, 2 , 2, 0x000000);

	// _renderLib->drawSquare(0, 1 , 1, 0x00FF00);
	// _renderLib->drawSquare(1, 1 , 1, 0x000000);
	// _renderLib->drawSquare(0, 0 , 1, 0x00FF00);
	// _renderLib->drawCircle(0,0, 1, 0x000000);
	// _renderLib->drawCircle(0,2, 2, 0x000000);
	// _renderLib->drawCircle(0,4, 2, 0x000000);

	// 
	return true;
}



