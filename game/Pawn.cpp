#include "Pawn.hpp"

Pawn::Pawn( void )
{
	return ;
}

Pawn::Pawn( int player) : _player( player )
{
	std::cout << "PAWN CONST: " << _player << std::endl;
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

int		Pawn::getPlayer()
{
	return this->_player;
}