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

