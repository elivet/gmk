#include "Player.hpp"

Player::Player( void ) : _name(1), _capturedPawns(0), _color(0x000000)
{
	return ;
}

Player::Player( int name, int color ) : _name(name), _capturedPawns(0), _color(color)
{
	return ;
}

Player::~Player( void )
{
	return ;
}

Player::Player( Player const & src )
{
	*this = src;
}

Player &	Player::operator=( Player const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

std::pair<int, int>		Player::play(Board* currentBoard, std::pair<int, int> xy)
{
	std::cout << this->_name << " playing" << std::endl;
	// std::pair<int, int> key = std::make_pair(4, 5);
	// (void)currentBoard;
	// (void)xy;
	// return key;
	this->referee(currentBoard, xy);
	return xy;
}

bool					Player::referee(Board* currentBoard, std::pair<int, int> key)
{
	int		x = key.first;
	int		y = key.second;

	if (x > 18 || x < 0 || y > 18 || y < 0)
		return ( false );
	if (currentBoard->findPawn(x, y))
		return (false);
	return ( true );
}

int						Player::getName() const
{
	return this->_name;
}

int						Player::getColor() const
{
	return this->_color;
}


