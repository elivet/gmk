#include "Possibility.hpp"

Possibility::Possibility( void )
{
	return ;
}

Possibility::Possibility( int x, int y, int player ): _player(player), _x(x), _y(y)
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