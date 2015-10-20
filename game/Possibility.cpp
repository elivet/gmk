#include "Possibility.hpp"

Possibility::Possibility( void )
{
	return ;
}

Possibility::Possibility( int x, int y, int player ): _player(player), _x(x), _y(y)
{
	std::cout << "tg : " << _player << std::endl;
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


void		Possibility::insert(int x, int y, int player)
{
	std::pair<int, int>		xy = std::make_pair(x, y);
	Possibility	*possibility = new Possibility(x, y, player);
	_grandSons[xy] = possibility;
	return ;
}



int		Possibility::getX( void )
{
	return this->_x;
}

int		Possibility::getY( void )
{
	return this->_y;
}

std::map<std::pair<int,int>,Possibility*>	Possibility::getGrandSons( void )
{
	return this->_grandSons;
}