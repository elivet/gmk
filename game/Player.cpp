#include "Player.hpp"

Player::Player( void ) : _name(1), _capturedPawns(0)
{
	return ;
}

Player::Player( int name ) : _name(name), _capturedPawns(0)
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

std::pair<int, int>		Player::play()
{
	std::cout << this->_name << " playing" << std::endl;
	std::pair<int, int> key = std::make_pair(1, 4);
	return key;
}

int						Player::getName()
{
	return this->_name;
}