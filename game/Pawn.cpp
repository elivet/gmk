#include "../includes/Pawn.hpp"

Pawn::Pawn( void )
{
	return ;
}

Pawn::Pawn( int x, int y, int player)  : _xPos( x ), _yPos( y ), _player( player )
{
	return ;
}

Pawn::~Pawn( void )
{
	return ;
}

Pawn::Pawn( Pawn const & src )
{
	*this = src;
}

Pawn &	Pawn::operator=( Pawn const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}