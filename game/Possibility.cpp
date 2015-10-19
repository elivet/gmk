#include "Possibility.hpp"

Possibility::Possibility( void )
{
	return ;
}

Possibility( int x, int y, int player ): _x(x), _y(y), _player(player)
{
	return ;
}

Possibility::~Possibility( void )
{
	return ;
}

Possibility::Possibility( Possibility const & src )
{
	*this = src;
}

Possibility &	Possibility::operator=( Possibility const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}