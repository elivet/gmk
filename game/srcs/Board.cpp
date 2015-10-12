#include "../includes/Board.hpp"

Board::Board( void )
{
	return ;
}

Board::~Board( void )
{
	return ;
}

Board::Board( Board const & src )
{
	*this = src;
}

Board &	Board::operator=( Board const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}