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