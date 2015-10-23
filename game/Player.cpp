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
	std::pair<int, int> key = std::make_pair(4, 5);
	(void)currentBoard;
	(void)xy;
	return key;
}

int						Player::getName() const
{
	return this->_name;
}

int						Player::getColor() const
{
	return this->_color;
}


