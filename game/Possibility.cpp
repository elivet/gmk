#include "Possibility.hpp"

Possibility::Possibility( void )
{
	_weight = -1 * 2147483648;
	return ;
}

Possibility::Possibility( int x, int y, int player ): _player(player), _x(x), _y(y)
{
	// std::cout << "tg : " << _player << std::endl;
	_player = player;
	_weight = -1 * 2147483648;
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

bool Possibility::operator==(Possibility &rhs)
{
	return(
		this->_player == rhs.getPlayerName() &&
		this->_x == rhs.getX() &&
		this->_y == rhs.getY() &&
		this->_weight == rhs.getWeight() &&
		this->_capturedPawns.size() == rhs._capturedPawns.size()
	);
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

int		Possibility::getWeight( void )
{
	return this->_weight;
}

int		Possibility::getPlayerName( void )
{
	return this->_player;
}

std::map<std::pair<int,int>,Possibility*>	Possibility::getGrandSons( void )
{
	return this->_grandSons;
}

void 				Possibility::setWeight(int weight)
{
	_weight = weight;
	return ;
}














