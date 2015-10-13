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